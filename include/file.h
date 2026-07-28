#ifndef FILE_H
#define FILE_H

#include "tasks.h"

void saveTaskList(char *file_name, TaskList *ls);
void createTaskList(char *file_name, TaskList *ls);

#endif