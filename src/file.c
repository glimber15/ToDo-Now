// #include <stddef.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "tasks.h"

// void saveTaskList(char *file_name, TaskList *ls) {
// 	FILE *file = fopen(file_name, "wb");
// 	if (file == NULL) {
// 		perror("binary file creation failed");
// 		return;
// 	}
// 	// number of tasks
// 	fwrite(&ls->taskCount, sizeof(ls->taskCount), 1, file);

// 	for (int i = 0; i < ls->taskCount; i++) {
// 		char *title = ls->tasks[i].title;
// 		size_t len = strlen(title) + 1;

// 		// size of title
// 		if (fwrite(&len, sizeof(len), 1, file) != 1) {
// 			perror("writting task title size failed");
// 			fclose(file);
// 			return;
// 		}
// 		// title array/string
// 		if (fwrite(title, 1, len, file) != len) {
// 			perror("writting task title string failed");
// 			fclose(file);
// 			return;
// 		}
// 		// state
// 		if (fwrite(&ls->tasks[i].state, sizeof(ls->tasks[i].state), 1, file) != 1) {
// 			perror("writting task title state failed");
// 			fclose(file);
// 			return;
// 		}
// 	}
// 	fclose(file);
// }

// void createTaskList(char *file_name, TaskList *ls) {
// 	FILE *file = fopen(file_name, "rb");
// 	if (file == NULL) {
// 		perror("opening file to read");
// 		return;
// 	}

// 	fread(&ls->taskCount, sizeof(ls->taskCount), 1, file);
// 	ls->size = ls->taskCount;

// 	ls->tasks = malloc(ls->size * sizeof(Task));
// 	if (ls->tasks == NULL) {
// 		fclose(file);
// 		perror("malloc tasks");
// 		return;
// 	}

// 	for (int i = 0; i < ls->taskCount; i++) {
// 		size_t len;

// 		// title length
// 		if (fread(&len, sizeof(len), 1, file) != 1) {
// 			fclose(file);
// 			perror("read task title length");
// 			return;
// 		}
// 		ls->tasks[i].title = malloc(len);
// 		if (ls->tasks[i].title == NULL) {
// 			fclose(file);
// 			perror("malloc task title");
// 			return;
// 		}
// 		// title
// 		if (fread(ls->tasks[i].title, 1, len, file) != len) {
// 			fclose(file);
// 			perror("read task title");
// 			return;
// 		}
// 		// state
// 		if (fread(&ls->tasks[i].state, sizeof(ls->tasks[i].state), 1, file) != 1) {
// 			fclose(file);
// 			perror("read task state");
// 			return;
// 		}
// 		// id
// 		ls->tasks[i].id = i;
// 	}
// 	fclose(file);
// }