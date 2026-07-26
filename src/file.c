#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "tasks.h"

void formatFile(FILE *file, TaskList *ls) {
	size_t buffer_size = 8;
	char *buffer = malloc(buffer_size);
	file = fopen("tasks.txt", "w");
	// TDOD: make the file from `ls`
	fclose(file);
}