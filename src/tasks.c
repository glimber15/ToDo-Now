#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include "tasks.h"

void createDb(sqlite3 **db) {
	// TODO: create .tsk folder if not found
	int rc = sqlite3_open(".tsk/tasks.db", db);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(*db));
		sqlite3_close(*db);
	}
}

void createTasksTable(sqlite3 *db) {
	const char *sql = 
		"CREATE TABLE IF NOT EXISTS tasks("
		"id INTEGER PRIMARY KEY,"
		"title TEXT NOT NULL,"
		"state INTEGER NOT NULL DEFAULT 0"
		");";
	
	char *err_msg = NULL;

	if (sqlite3_exec(db, sql, NULL, NULL, &err_msg) != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", err_msg);
	}

	free(err_msg);
}

void initTasks(sqlite3 **db) {
	createDb(db);
	createTasksTable(*db);
}

void addTask(sqlite3 *db, const char *title) {
	const char *sql = "INSERT INTO tasks (title) VALUES (?);";
	sqlite3_stmt *stmt;

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
		return;
	}

	if (sqlite3_bind_text(stmt, 1, title, -1, SQLITE_TRANSIENT) != SQLITE_OK) {
		fprintf(stderr, "Failed to bind title\n");
		return;
	}

	if (sqlite3_step(stmt) != SQLITE_DONE) {
		fprintf(stderr, "Failed to add task: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		return;
	}

	sqlite3_finalize(stmt);

	printf("Added task: %lld '%s'\n", sqlite3_last_insert_rowid(db), title);
}

void displayTasks(sqlite3 *db) {
	const char *sql = "SELECT * FROM tasks ORDER BY id;";
	sqlite3_stmt *stmt;

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
		return;
	}

	int rc = sqlite3_step(stmt);

	if (rc == SQLITE_DONE) {
		printf("There are no tasks!\n");
		sqlite3_finalize(stmt);
		return;
	}

	while (rc == SQLITE_ROW) {
		int id = sqlite3_column_int(stmt, 0);
		const char *title = (char *)sqlite3_column_text(stmt, 1);
		int state = sqlite3_column_int(stmt, 2);

		char symbol = state ? '#' : ' ';

		printf("%d [%c] %s\n", id, symbol, title);

		rc = sqlite3_step(stmt);
	}

	sqlite3_finalize(stmt);
}

// TODO: Move or archive completed tasks
void toggleTask(sqlite3 *db, int id) {
	const char *sql = 
		"UPDATE tasks "
		"SET state = NOT state "
		"WHERE id = ? "
		"RETURNING title, state;";
	sqlite3_stmt *stmt;

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
		return;
	}

	if (sqlite3_bind_int(stmt, 1, id) != SQLITE_OK) {
		fprintf(stderr, "Failed to bind task id\n");
		return;
	}

	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		const char *title = (const char *)sqlite3_column_text(stmt, 0);
		int state = sqlite3_column_int(stmt, 1);

		if (state)
			printf("Task Complete: %d - '%s'\n", id, title);
		else
			printf("Task Unchecked: %d - '%s'\n", id, title);

		sqlite3_finalize(stmt);
		return;
	}

	if (rc == SQLITE_DONE)
		fprintf(stderr, "Task %d does not exist\n", id);
	else {
		fprintf(stderr, "Failed to update task state: %s\n", sqlite3_errmsg(db));
	}

	sqlite3_finalize(stmt);
}

void deleteTask(sqlite3 *db, int id) {
	const char *sql = 
		"DELETE FROM tasks "
		"WHERE id = ? "
		"RETURNING title";
	sqlite3_stmt *stmt;

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
		return;
	}

	if (sqlite3_bind_int(stmt, 1, id) != SQLITE_OK) {
		fprintf(stderr, "Failed to bind task id\n");
		return;
	}

	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		const char *title = (const char *)sqlite3_column_text(stmt, 0);
		
		printf("Task deleted: %d - '%s'\n", id, title);

		sqlite3_finalize(stmt);
		return;
	}

	if (rc == SQLITE_DONE)
		fprintf(stderr, "Task %d does not exist\n", id);
	else {
		fprintf(stderr, "Failed to delete task: %s\n", sqlite3_errmsg(db));
	}

	sqlite3_finalize(stmt);
}

// void deleteCheckedTasks(TaskList *ls) {
// 	int un_checked = 0;

// 	for (int i = 0; i < ls->taskCount; i++) {
// 		if (!ls->tasks[i].state) {
// 			if (un_checked != i)
// 				ls->tasks[un_checked] = ls->tasks[i];
// 			ls->tasks[un_checked].id = un_checked;
// 			un_checked++;
// 		}
// 		else
// 			free(ls->tasks[i].title);
// 	}

// 	ls->taskCount = un_checked;

// 	printf("Deleted checked tasks.\n");
// }

// TODO: display previous task and new task in response
void editTask(sqlite3 *db, int id, const char *new_title) {
	const char *sql = 
		"UPDATE tasks "
		"SET title = ? "
		"WHERE id = ?;";
	sqlite3_stmt *stmt;

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
		return;
	}

	if (sqlite3_bind_text(stmt, 1, new_title, -1, SQLITE_TRANSIENT) != SQLITE_OK) {
		fprintf(stderr, "Failed to bind task new title\n");
		sqlite3_finalize(stmt);
		return;
	}

	if (sqlite3_bind_int(stmt, 2, id) != SQLITE_OK) {
		fprintf(stderr, "Failed to bind task id\n");
		sqlite3_finalize(stmt);
		return;
	}

	if (sqlite3_step(stmt) != SQLITE_DONE) {
		fprintf(stderr, "Failed to edit task: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		return;
	}

	printf("Task edited: %d - '%s'\n", id, new_title);

	sqlite3_finalize(stmt);
}

void clearData(sqlite3 *db) {
	const char *sql = "DELETE FROM tasks;";
	char *err_msg = NULL;

	if (sqlite3_exec(db, sql, NULL, NULL, &err_msg) != SQLITE_OK) {
		fprintf(stderr, "Failed to clear tasks\n");
		free(err_msg);
		return;
	}

	printf("Tasks data cleared!\n");
}
