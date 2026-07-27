#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "file.h"
#include "tasks.h"

void formatFile(char *file_name, TaskList *ls) {
	FILE *file = fopen(file_name, "wb");
	if (file == NULL) {
		perror("binary file creation failed");
		return;
	}
	for (int i = 0; i < ls->taskCount; i++) {
		char *title = ls->tasks[i].title;
		size_t len = strlen(title) + 1;

		// size of title
		if (fwrite(&len, sizeof(len), 1, file) != 1) {
			perror("writting task title size failed");
			fclose(file);
			return;
		}
		// title array/string
		if (fwrite(title, 1, len, file) != len) {
			perror("writting task title string failed");
			fclose(file);
			return;
		}
		// state
		if (fwrite(&ls->tasks[i].state, sizeof(ls->tasks[i].state), 1, file) != 1) {
			perror("writting task title state failed");
			fclose(file);
			return;
		}
	}
	fclose(file);
}

void createTaskList(char *file_name, TaskList *ls) {
	// TODO: create the task list struct from file
}