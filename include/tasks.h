#ifndef TASKS_H
#define TASKS_H

#include <stddef.h>
#include <stdio.h>

typedef struct {
	int id;
	char *title;
	int state;
} Task;

typedef struct {
	int size;
	int taskCount;
	Task *tasks;
} TaskList;

// tasks
void addTask(TaskList *ls, char *title);
void displayTasks(TaskList *list);
void toggleTask(TaskList *ls, int id);
void deleteTask(TaskList *ls, int id);
void editTask(TaskList *ls, int id, char *new_title);
void clearData(TaskList *ls);

// file
void saveTaskList(char *file_name, TaskList *ls);
TaskList createTaskList(char *file_name);

// helper
char *readLine(char *buffer, size_t *size, FILE *stream);
void printH(char *text, char dec);
void displayHelp();
int checkTaskExist(TaskList *ls, int id);
int confirm(char *dialog);

#endif