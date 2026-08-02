#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tasks.h"

void addTask(TaskList *ls, char *title) {
	if (strlen(title) == 1) {
		printf("ERROR: empty task title\n");
		return;
	}
	if (ls->taskCount == ls->size) {
		int new_size = ls->size + 10;
		Task *tmp = realloc(ls->tasks, new_size * sizeof(Task));
		if (tmp == NULL) {
			printf("ERROR: realloc new task failed!\n");
			return;
		}
		ls->tasks = tmp;
		ls->size = new_size;
	}

	Task newTask;
	newTask.id = ls->taskCount;
	newTask.state = 0;
	newTask.title = malloc(strlen(title) + 1);
	if (newTask.title == NULL) {
		printf("ERROR: malloc for new task failed!\n");
		return;
	}
	strcpy(newTask.title, title);
	ls->tasks[ls->taskCount] = newTask;
	ls->taskCount++;

	printf("Task Added! : [%d] %s\n", newTask.id, title);
}

void displayTasks(TaskList *ls) {
	if (ls->taskCount <= 0) {
		printf("You have no tasks.\n");
		return;
	}

	char state = ' ';
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
		printf("%d [ %c ] : %s\n", ls->tasks[i].id, state, ls->tasks[i].title);
	}
}

void toggleTask(TaskList *ls, int id) {
	if (!checkTaskExist(ls, id)) return;

	ls->tasks[id].state = !ls->tasks[id].state;
	
	if (ls->tasks[id].state)
		printf("Task Completed: [%d] %s\n", id, ls->tasks[id].title);
	else
		printf("Task Unchecked: [%d] %s\n", id, ls->tasks[id].title);
}

void deleteTask(TaskList *ls, int id) {
    if (!checkTaskExist(ls, id))
        return;

    free(ls->tasks[id].title);

    for (int i = id; i < ls->taskCount - 1; i++) {
        ls->tasks[i] = ls->tasks[i + 1];
        ls->tasks[i].id = i;
    }

    ls->taskCount--;
    printf("Task Deleted: [%d] %s\n", id, ls->tasks[id].title);
}

void deleteCheckedTasks(TaskList *ls) {
	int un_checked = 0;

	for (int i = 0; i < ls->taskCount; i++) {
		if (!ls->tasks[i].state) {
			if (un_checked != i)
				ls->tasks[un_checked] = ls->tasks[i];
			ls->tasks[un_checked].id = un_checked;
			un_checked++;
		}
		else
			free(ls->tasks[i].title);
	}

	ls->taskCount = un_checked;

	printf("Deleted checked tasks.\n");
}

void editTask(TaskList *ls, int id, char *new_title) {
	char *og_title = malloc(strlen(ls->tasks[id].title) + 1);
	if (og_title == NULL) {
		printf("ERROR: malloc edit task failed! (tmp title)");
		return;
	}
	strcpy(og_title, ls->tasks[id].title);
	char *tmp = realloc(ls->tasks[id].title, strlen(new_title) + 1);
	if (tmp == NULL) {
		printf("ERROR: realloc task edit failed!\n");
		return;
	}
	ls->tasks[id].title = tmp;
	strcpy(ls->tasks[id].title, new_title);
	og_title[strcspn(og_title, "\n")] = '\0';
	printf("Task Edited: %s -> %s", og_title, new_title);
}

void clearData(TaskList *ls) {
	Task *tmp = realloc(ls->tasks, sizeof(Task));
	if (tmp == NULL) {
		printf("ERROR: realloc task clear failed!\n");
		return;
	}
	ls->tasks = tmp;
	ls->size = 10;
	ls->taskCount = 0;
	printf("Task Data Cleared!\n");
}

