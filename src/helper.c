#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "tasks.h"

void printHelp() {
	printf(
		"usage                    tsk <action> <params...>\n\n"
		"actions:\n"
		"  init                     Initialize tasks in project dir\n"
		"  add 'task title'         Add a task\n"
		"  show                     Show tasks pending\n"
		"  show -c                  Show completed tasks also\n"
		"  tick <id>                Complete/toggle a task\n"
		"  edit <id> 'new title'    Edit a task title\n"
		"  del <id>                 Delete a task\n"
		"  kaboom                   Uninitaialize tasks\n"
	);
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
