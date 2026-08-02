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
		return 0;
	}
	else if (strcmp(argv[1], "h") == 0) {
		printHelp();
		return 0;
	}
	else if (strcmp(argv[1], "c") == 0) {
		if (argc < 3 || argc > 3) {
			printHelp();
			exit(EXIT_FAILURE);
		}
		
		float id;
		if (parseToNum(argv[2], &id)) {
			toggleTask(&list, id);
			saveTaskList(file, &list);
			return 0;
		}
		printHelp();
	}
	else if (strcmp(argv[1], "e") == 0) {
		if (argc < 4 || argc > 4) {
			printHelp();
			exit(EXIT_FAILURE);
		}

		float id;
		if (parseToNum(argv[2], &id)) {
			editTask(&list, id, argv[3]);
			saveTaskList(file, &list);
			return 0;
		}
		printHelp();
	}
	else if (strcmp(argv[1], "d") == 0) {
		if (argc < 3 || argc > 3) {
			printHelp();
			exit(EXIT_FAILURE);
		}
		
		float id;
		if (parseToNum(argv[2], &id)) {
			deleteTask(&list, id);
			saveTaskList(file, &list);
			return 0;
		}
		printHelp();
	}
	else if (strcmp(argv[1], "dc") == 0) {
		deleteCheckedTasks(&list);
		saveTaskList(file, &list);
		return 0;
	}
	else if (strcmp(argv[1], "x") == 0) {
		if (confirm("Clear all Data: ")) {
			clearData(&list);
			saveTaskList(file, &list);
			return 0;
		}
	}
	else printHelp();

	free(list.tasks);

	return 0;
}

