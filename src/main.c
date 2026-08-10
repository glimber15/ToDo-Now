#include <sqlite3.h>
#include <string.h>

#include "tasks.h"

int main(int argc, char **argv) {

	if (argc < 2) {
		printHelp();
		return 1;
	}

	sqlite3 *task_db = NULL;
	initTasks(&task_db);

	//
	// Add Task
	//
	if (strcmp(argv[1], "add") == 0) {
		if (argc < 3 || argc > 3) {
			printHelp();
			return 1;
		}
		addTask(task_db, argv[2]);
		return 0;
	}
	//
	// Show tasks
	//
	// TODO: add some parameters to format shown task list
	else if (strcmp(argv[1], "show") == 0) {
		displayTasks(task_db);
		return 0;
	}
	//
	// Toggle task
	//
	else if (strcmp(argv[1], "check") == 0) {
		if (argc < 3 || argc > 3) {
			printHelp();
			return 1;
		}
		
		float id;
		if (parseToNum(argv[2], &id)) {
			toggleTask(task_db, id);
			return 0;
		}
		printHelp();
	}
	//
	// Delete task
	//
	else if (strcmp(argv[1], "del") == 0) {
		if (argc < 3 || argc > 3) {
			printHelp();
			return 1;
		}
		
		float id;
		if (parseToNum(argv[2], &id)) {
			deleteTask(task_db, id);
			return 0;
		}
		printHelp();
	}
	//
	// Edit task
	//
	else if (strcmp(argv[1], "edit") == 0) {
		if (argc < 4 || argc > 4) {
			printHelp();
			return 1;
		}

		float id;
		if (parseToNum(argv[2], &id)) {
			editTask(task_db, id, argv[3]);
			return 0;
		}
		printHelp();
	}
	// // TODO: make `del`	have an extara param to delete checked
	// else if (strcmp(argv[1], "dc") == 0) {
	// 	deleteCheckedTasks(&list);
	// 	return 0;
	// }
	// else if (strcmp(argv[1], "clear") == 0) {
	// 	if (confirm("Clear all Data: ")) {
	// 		clearData(&list);
	// 		return 0;
	// 	}
	// }
	else if (strcmp(argv[1], "help") == 0) {
		printHelp();
		return 0;
	}
	else printHelp();

	sqlite3_close(task_db);

	return 0;
}

