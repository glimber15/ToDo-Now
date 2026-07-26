#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tasks.h"

void addTask(TaskList *ls, char *title) {
	// TODO: Check if emply
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

	printf("Task Added! : [%d] %s\n", ls->taskCount, title);
}

void displayTasks(TaskList *ls) {
	if (ls->taskCount <= 0) {
		printf("You have no tasks.\n");
		return;
	}

	printH("Tasks", '-');
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
		printf("%d [ %c ] : %s", ls->tasks[i].id, state, ls->tasks[i].title);
	}
}

int checkTaskExist(TaskList *ls, int id) {
	if (ls->taskCount == 0) {
		printf("You have no tasks.\n");
		return 0;
	}
	if (id >= ls->taskCount) {
		printf("Task does not exist. Use \'S\' to show tasks.\n");
		return 0;
	}
	return 1;
}

void toggleTask(TaskList *ls, int id) {
	if (!checkTaskExist(ls, id)) return;

	// flip b/w 0 and 1
	ls->tasks[id].state = !ls->tasks[id].state;
	// TODO: responce
}

void deleteTask(TaskList *ls, int id) {
	if (!checkTaskExist(ls, id)) return;

	char *task = ls->tasks[id].title;
	for (int i = 0; i < ls->size - 1; i++) {
		ls->tasks[i] = ls->tasks[i + 1];
		ls->tasks[i].id--;
	}
	int new_size = ls->size--;
	Task *tmp = realloc(ls->tasks, new_size * sizeof(Task));
	if (tmp == NULL) {
		printf("ERROR: realloc task delete failed!\n");
		return;
	}
	ls->tasks = tmp;
	ls->size = new_size;
	ls->taskCount--;
	printf("Task Deleted: [%d] : %s", id, task);
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

void displayHelp() {
	printH("Helps", '-');
	printf("H : Show this again.\n");
	printf("Q : Quit.\n");
	printf("A : Add a new task.\n");
	printf("S : Show tasks.\n");
	printf("C : Toggle task.\n");
	printf("E : Edit task.\n");
	printf("D : Delete task.\n");
}

char *readLine(char *buffer, size_t *size, FILE *stream) {
	size_t len = 0;
	while (fgets(buffer + len, *size - len, stream)) {
		len += strlen(buffer + len);
		if (len > 0 && buffer[len - 1] == '\n') {
			break;
		}
		*size *= 2;
		char *tmp = realloc(buffer, *size);
		if (tmp == NULL) {
			perror("realloc buffer");
			free(tmp);
			return NULL;
		}
		buffer = tmp;
	}
	return buffer;
}

void printH(char *text, char dec) {
	int t_len = 0;
	int r_len = 0;
	int spacing = 0;
	while (text[t_len] != '\0') {
		t_len++;
	}
	r_len = (t_len * 4) + 1;
	spacing = (r_len/2) - (t_len/2);
	if (t_len % 2 != 0) r_len += 1;

	for (int i = 0; i <= r_len; i++) printf("%c", dec);
	printf("\n");
	printf("%c", dec);
	for (int i = 0; i < spacing; i++) printf(" ");
	printf("%s", text);
	for (int i = 0; i < spacing; i++) printf(" ");
	printf("%c", dec);
	printf("\n");
	for (int i = 0; i <= r_len; i++) printf("%c", dec);
	printf("\n");
}

int confirm(char *dialog) {
	char input;
	printf("%s", dialog);
	printf("(Y/N)?");
	scanf("%c", &input);
	getchar();
	if (input == 'Y' || input == 'y') return 1;
	else if (input == 'N' || input == 'n') return 0;
	else {
		printf("Undifined input: Type \'H\' for help.\n");
		return 0;
	}
}