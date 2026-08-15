#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include "tasks.h"

void createDb(sqlite3 **db) {
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

    if (sqlite3_exec(db, sql, NULL, NULL, &err_msg) != SQLITE_OK)
        fprintf(stderr, "SQL error: %s\n", err_msg);

    sqlite3_free(err_msg);
}

void initTasks() {
    if (mkdir(".tsk", 0755) == -1 && errno != EEXIST) {
        perror("Failed to create dir '.tsk'!");
    return;
    }

    printf("tsk initialized successfully!\n");
}
