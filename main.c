#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int id;
	char *title;
} Task;

typedef struct {
	int size;
	int taskCount;
	Task *tasks;
} TaskList;

void greetUser();
void addTask(TaskList *ls, char *title);
void displayTasks(TaskList *list);
void toggleTask();
void editTask();
void deleteTask();
void clearData();

int main() {

	greetUser();

	TaskList list;
	list.size = 10;
	list.taskCount = 0;
	list.tasks = malloc(list.size * sizeof(Task));

	char task[255];

	printf("Add a new Task: ");
	scanf("%s", task);
	addTask(&list, task);

	displayTasks(&list);

	free(list.tasks);

	return 0;
}

void addTask(TaskList *ls, char *title) {
	if (ls->taskCount == ls->size) {
		int new_size = ls->size + 10;
		Task *tmp = realloc(ls->tasks, new_size * sizeof(Task));
		if (tmp == NULL) {
			printf("ERROR: realloc failed!\n");
			return;
		}
		ls->tasks = tmp;
		ls->size = new_size;
	}

	Task newTask;
	newTask.id = ls->taskCount;
	newTask.title = malloc(strlen(title) + 1);
	if (newTask.title == NULL) {
		printf("ERROR: malloc for new task failed!\n");
		return;
	}
	strcpy(newTask.title, title);
	ls->tasks[ls->taskCount] = newTask;
	ls->taskCount++;

	printf("Task Added! : %s\n", title);
}

void displayTasks(TaskList *list) {
	for (int i = 0; i < list->taskCount; i++) {
		printf("%s\n", list->tasks[i].title);
	}
}

void greetUser() {
	printf("\n************************\n");
	printf("\tTODO CLI");
	printf("\n************************\n");
}