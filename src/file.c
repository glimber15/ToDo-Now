#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "tasks.h"

void formatFile(FILE *file, TaskList *ls) {
	char state = ' ';
	file = fopen("tasks.txt", "w");
	if (file == NULL) {
		perror("file format, creation");
		return;
	}
	// TODO: format after checking/toggling, deleting, editing
	for (int i = 0; i < ls->taskCount; i++) {
		switch (ls->tasks[i].state) {
			case 0:
				state = ' ';
				break;
			case 1:
				state = '#';
				break;
			default:
				state = '.';
				break;
		}
		fprintf(file, "%d [%c] %s", ls->tasks[i].id, state, ls->tasks[i].title);
	}
	fclose(file);
}