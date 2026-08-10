#ifndef TASKS_H
#define TASKS_H

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <sqlite3.h>

extern sqlite3 *task_db;

typedef struct {
	int id;
	char *title;
	int state;
} Task;

//database
void createDb(sqlite3 **db);
void createTasksTable(sqlite3 *db);
void initTasks(sqlite3 **db);


// tasks
void addTask(sqlite3 *db, const char *title);
void displayTasks(sqlite3 *db);
void toggleTask(sqlite3 *db, int id);
// void deleteTask(sqlite3 *db, int id);
// void deleteCheckedTasks(sqlite3 *db);
// void editTask(sqlite3 *db, int id, const char *new_title);
// void clearData(sqlite3 *db);

// // file
// void saveTaskList(const char *file_name, sqlite3 *db);
// void createTaskList(const char *file_name, sqlite3 *db);

// helper
// void initTasks(const char *file);
// char *readLine(char *buffer, size_t *size, FILE *stream);
bool parseToNum(const char *str, float *result);
// //bool checkTaskExist(sqlite3 *db, int id);

// bool confirm(const char *dialog);
// void printHead(char *text, char dec);
void printHelp();

#endif