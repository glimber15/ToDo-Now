#ifndef TASKS_H
#define TASKS_H

#include <sqlite3.h>
#include <stdbool.h>
#include <stddef.h>

extern sqlite3 *task_db;

typedef struct {
  int id;
  char *title;
  int state;
} Task;

// database
void createDb(sqlite3 **db);
void createTasksTable(sqlite3 *db);
void initTasks();

// tasks
void addTask(sqlite3 *db, const char *title);
void displayTasks(sqlite3 *db, int state, const char *title);
void toggleTask(sqlite3 *db, int id);
void deleteTask(sqlite3 *db, int id);
void editTask(sqlite3 *db, int id, const char *new_title);
void clearData(sqlite3 *db);

// helper
bool parseToNum(const char *str, float *result);
bool confirm(const char *dialog);
void printHelp();

#endif
