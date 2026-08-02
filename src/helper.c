#include <stdlib.h>
#include <string.h>

#include "tasks.h"

void initTasks() {
	
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