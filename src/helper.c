#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tasks.h"

void printHelp() {
	printf(
			"Usage: task <operation> <parameters>\n\n"
			"Add task: task a \"<task title>\"\n"
			"Show tasks: task s\n"
			"Check/Toggle task: task c <task id>\n"
			"Edit task: task e <task id> \"<new task title>\"\n"
			"Delete task: task d <task id>\n"
			"Delete completed tasks: task dc\n"
			"Clear task data: task x\n"
		);
}

// char *readLine(char *buffer, size_t *size, FILE *stream) {
// 	size_t len = 0;
// 	while (fgets(buffer + len, *size - len, stream)) {
// 		len += strlen(buffer + len);
// 		if (len > 0 && buffer[len - 1] == '\n') {
// 			break;
// 		}
// 		*size *= 2;
// 		char *tmp = realloc(buffer, *size);
// 		if (tmp == NULL) {
// 			perror("realloc buffer");
// 			free(tmp);
// 			return NULL;
// 		}
// 		buffer = tmp;
// 	}
// 	return buffer;
// }

bool parseToNum(const char *str, float *result) {
	char *end;
	*result = strtod(str, &end);
	return *end == '\0';
}

// void printHead(char *text, char dec) {
// 	int t_len = 0;
// 	int r_len = 0;
// 	int spacing = 0;
// 	while (text[t_len] != '\0') {
// 		t_len++;
// 	}
// 	r_len = (t_len * 4) + 1;
// 	spacing = (r_len/2) - (t_len/2);
// 	if (t_len % 2 != 0) r_len += 1;

// 	for (int i = 0; i <= r_len; i++) printf("%c", dec);
// 	printf("\n");
// 	printf("%c", dec);
// 	for (int i = 0; i < spacing; i++) printf(" ");
// 	printf("%s", text);
// 	for (int i = 0; i < spacing; i++) printf(" ");
// 	printf("%c", dec);
// 	printf("\n");
// 	for (int i = 0; i <= r_len; i++) printf("%c", dec);
// 	printf("\n");
// }

// bool confirm(char *dialog) {
// 	char input;
// 	printf("%s", dialog);
// 	printf("(y/N)?");
// 	scanf("%c", &input);
// 	getchar();
// 	if (input == 'Y' || input == 'y')
// 		return true;
// 	else if (input == 'N' || input == 'n')
// 		return false;
// 	else {
// 		printHelp();
// 		return false;
// 	}
// }