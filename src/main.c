#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tasks.h"

int main(int argc, char **argv) {

	if (argc < 2) {
		printHelp();
		exit(EXIT_FAILURE);
	}

	// save file
	char *file = "tasks.bin";

	initTasks(file);

	if (strcmp(argv[1], "s") == 0) {
		displayTasks(&list);
		return 0;
	}
	else if (strcmp(argv[1], "a") == 0) {
		if (argc < 3 || argc > 3) {
			printHelp();
			exit(EXIT_FAILURE);
		}
		addTask(&list, argv[2]);
		saveTaskList(file, &list);
	}

	// while (1) {
	// 	printf("----------\n");
	// 	printf("> ");
	// 	scanf("%c", &usrInput);
	// 	while (getchar() != '\n');
	// 	if (usrInput == 'A' || usrInput == 'a') {
	// 		printf("Add Task: ");
	// 		task = readLine(task, &task_input_size, stdin);
	// 		addTask(&list, task);
	// 		saveTaskList(file, &list);
	// 	}
	// 	else if (usrInput == 'S' || usrInput == 's') {
	// 		displayTasks(&list);
	// 	}
	// 	else if (usrInput == 'H' || usrInput == 'h') {
	// 		displayHelp();
	// 	}
	// 	else if (usrInput == 'C' || usrInput == 'c') {
	// 		int id = 0;
	// 		printf("Enter task ID:\n> ");
	// 		scanf("%d", &id);
	// 		toggleTask(&list, id);
	// 		saveTaskList(file, &list);
	// 		getchar();
	// 	}
	// 	else if (usrInput == 'E' || usrInput == 'e') {
	// 		int id = 0;
	// 		printf("Enter task ID:\n> ");
	// 		scanf("%d", &id);
	// 		getchar();
	// 		if (!checkTaskExist(&list, id)) continue;
	// 		printf("Edit Task : %s> ", list.tasks[id].title);
	// 		fgets(task, sizeof(task), stdin);
	// 		editTask(&list, id, task);
	// 		saveTaskList(file, &list);
	// 	}
	// 	else if (usrInput == 'D' || usrInput == 'd') {
	// 		int id = 0;
	// 		printf("Enter task ID:\n> ");
	// 		scanf("%d", &id);
	// 		deleteTask(&list, id);
	// 		saveTaskList(file, &list);
	// 		getchar();
	// 	}
	// 	else if (usrInput == 'X' || usrInput == 'x') {
	// 		if (confirm("Clear all Data: ")) {
	// 			clearData(&list);
	// 			saveTaskList(file, &list);
	// 		}
	// 	}
	// 	else if (usrInput == 'Q' || usrInput == 'q') {
	// 		printf("Bay :)\n");
	// 		break;
	// 	}
	// 	else {
	// 		printf("Undifined input: Type \'H\' for help.\n");
	// 	}
	// }

	free(list.tasks);

	return 0;
}

