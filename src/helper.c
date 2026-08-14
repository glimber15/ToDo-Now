#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "tasks.h"

void printHelp() {
  printf("Usage: task <operation> <parameters>\n\n"
         "Add task: tsk add \"<task title>\"\n"
         "Show tasks: tsk show\n"
         "Show completed tasks: tsk show -c\n"
         "Check/Toggle task: tsk check <task id>\n"
         "Edit task: tsk edit <task id> \"<new task title>\"\n"
         "Delete task: tsk del <task id>\n"
         "Clear task data: tsk clear\n");
}

bool parseToNum(const char *str, float *result) {
  char *end;
  *result = strtod(str, &end);
  return *end == '\0';
}

bool confirm(const char *dialog) {
  char input;
  printf("%s", dialog);
  printf("(y/N)?");
  scanf("%c", &input);
  getchar();
  if (input == 'Y' || input == 'y')
    return true;
  else if (input == 'N' || input == 'n')
    return false;
  else {
    printHelp();
    return false;
  }
}
