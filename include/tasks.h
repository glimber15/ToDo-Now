#ifndef TASKS_H
#define TASKS_H


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

void addTask(TaskList *ls, char *title);
void displayTasks(TaskList *list);
void toggleTask(TaskList *ls, int id);
void deleteTask(TaskList *ls, int id);
void editTask(TaskList *ls, int id, char *new_title);
void clearData(TaskList *ls);

void printH(char *text, char dec);
void displayHelp();
int checkTaskExist(TaskList *ls, int id);
int confirm(char *dialog);

#endif