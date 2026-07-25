#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int id;
	char *title;
	int state;
} Task;

typedef struct {
	int size;
	int taskCount;
	Task *tasks;
} TaskList;

// TODO: Move these to a different file
// Print a heading with a box border `dec`
void printH(char *text, char dec);

void addTask(TaskList *ls, char *title);
void displayTasks(TaskList *list);
void displayHelp();
void toggleTask(TaskList *ls, int id);
void deleteTask(TaskList *ls, int id);

void editTask(TaskList *ls, int id, char *new_title);
void clearData();
// TODO: Free the taskList and Task objects
void freeTaskMemory(TaskList *ls);
int checkTaskExist(TaskList *ls, int id);

int main() {
	// User action input
	char usrInput = ' ';
	// Task List
	TaskList list;
	list.size = 10;
	list.taskCount = 0;
	list.tasks = malloc(list.size * sizeof(Task));

	printH("TODO CLI", '=');

	if (list.tasks == NULL) {
		printf("ERROR: malloc task list failed!");
		return 1;
	}

	// TODO: dynamic memory?
	// used to get the task title when adding it
	char *task = malloc(100);

	displayHelp();

	while (1) {
		printf("----------\n");
		printf("> ");
		scanf("%c", &usrInput);
		while (getchar() != '\n');
		if (usrInput == 'A' || usrInput == 'a') {
			printf("Add Task: ");
			fgets(task, sizeof(task), stdin);
			addTask(&list, task);
		}
		else if (usrInput == 'S' || usrInput == 's') {
			displayTasks(&list);
		}
		else if (usrInput == 'H' || usrInput == 'h') {
			displayHelp();
		}
		else if (usrInput == 'C' || usrInput == 'c') {
			int id = 0;
			printf("Enter task ID:\n> ");
			scanf("%d", &id);
			toggleTask(&list, id);
			getchar();
		}
		else if (usrInput == 'E' || usrInput == 'e') {
			int id = 0;
			printf("Enter task ID:\n> ");
			scanf("%d", &id);
			getchar();
			if (!checkTaskExist(&list, id)) continue;
			printf("Edit Task: ");
			fgets(task, sizeof(task), stdin);
			editTask(&list, id, task);
		}
		else if (usrInput == 'D' || usrInput == 'd') {
			int id = 0;
			printf("Enter task ID:\n> ");
			scanf("%d", &id);
			deleteTask(&list, id);
			getchar();
		}
		else if (usrInput == 'Q' || usrInput == 'q') {
			printf("Bay :)\n");
			break;
		}
		else {
			printf("Undifined input: Type \'H\' for help.\n");
		}
	}

	free(list.tasks);

	return 0;
}

void addTask(TaskList *ls, char *title) {
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
	char *tmp = realloc(ls->tasks[id].title, strlen(new_title) + 1);
	if (tmp == NULL) {
		printf("ERROR: realloc task edit failed!\n");
		return;
	}
	ls->tasks[id].title = tmp;
	strcpy(ls->tasks[id].title, new_title);
	// TODO: responce
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
	char ruler[r_len];

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
