#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tasks.h"
#include "file.h"

void freeTaskMemory(TaskList *ls);

int main() {
	char *file = "tasks.bin";
	// User action input
	char usrInput = ' ';
	// Task List
	TaskList list;
	createTaskList(file, &list);
	if (list.taskCount <= 0) {
		list.size = 10;
		list.taskCount = 0;
		list.tasks = malloc(list.size * sizeof(Task));
	}

	printH("TODO CLI", '=');

	if (list.tasks == NULL) {
		printf("ERROR: malloc task list failed!");
		return 1;
	}

	// TODO: dynamic memory?
	// used to get the task title when adding it
	size_t task_input_size = 8;
	char *task = malloc(task_input_size);

	displayHelp();

	while (1) {
		printf("----------\n");
		printf("> ");
		scanf("%c", &usrInput);
		while (getchar() != '\n');
		if (usrInput == 'A' || usrInput == 'a') {
			printf("Add Task: ");
			task = readLine(task, &task_input_size, stdin);
			addTask(&list, task);
			saveTaskList(file, &list);
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
			saveTaskList(file, &list);
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
			saveTaskList(file, &list);
		}
		else if (usrInput == 'D' || usrInput == 'd') {
			int id = 0;
			printf("Enter task ID:\n> ");
			scanf("%d", &id);
			deleteTask(&list, id);
			saveTaskList(file, &list);
			getchar();
		}
		else if (usrInput == 'X' || usrInput == 'x') {
			if (confirm("Clear all Data: ")) {
				clearData(&list);
				saveTaskList(file, &list);
			}
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

