#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tasks.h"

FILE *t_file;


char *readLine(char *buffer, size_t *size, FILE *stream);
void freeTaskMemory(TaskList *ls);

int main() {
	// User action input
	char usrInput = ' ';
	// Task List
	TaskList list;
	list.size = 10;
	list.taskCount = 0;
	list.tasks = malloc(list.size * sizeof(Task));

	printH("TODO CLI", '=');

	if (list.tasks == NULL) {
		printf("ERROR: malloc task list failed!");
		return 1;
	}

	// TODO: dynamic memory?
	// used to get the task title when adding it
	char *task = malloc(100);

	displayHelp();

	while (1) {
		printf("----------\n");
		printf("> ");
		scanf("%c", &usrInput);
		while (getchar() != '\n');
		if (usrInput == 'A' || usrInput == 'a') {
			printf("Add Task: ");
			fgets(task, sizeof(task), stdin);
			addTask(&list, task);
		}
		else if (usrInput == 'S' || usrInput == 's') {
			displayTasks(&list);
		}
		else if (usrInput == 'H' || usrInput == 'h') {
			displayHelp();
		}
		else if (usrInput == 'C' || usrInput == 'c') {
			int id = 0;
			printf("Enter task ID:\n> ");
			scanf("%d", &id);
			toggleTask(&list, id);
			getchar();
		}
		else if (usrInput == 'E' || usrInput == 'e') {
			int id = 0;
			printf("Enter task ID:\n> ");
			scanf("%d", &id);
			getchar();
			if (!checkTaskExist(&list, id)) continue;
			printf("Edit Task: ");
			fgets(task, sizeof(task), stdin);
			editTask(&list, id, task);
		}
		else if (usrInput == 'D' || usrInput == 'd') {
			int id = 0;
			printf("Enter task ID:\n> ");
			scanf("%d", &id);
			deleteTask(&list, id);
			getchar();
		}
		else if (usrInput == 'X' || usrInput == 'x') {
			if (confirm("Clear all Data: ")) clearData(&list);
		}
		else if (usrInput == 'Q' || usrInput == 'q') {
			printf("Bay :)\n");
			break;
		}
		else {
			printf("Undifined input: Type \'H\' for help.\n");
		}
	}

	free(list.tasks);

	return 0;
}

