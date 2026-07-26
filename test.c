#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *file;

char *readLine(char *buffer, size_t *size, FILE *stream) {
	size_t len = 0;
	while (fgets(buffer + len, *size - len, stream)) {
		len += strlen(buffer + len);
		if (len > 0 && buffer[len - 1] == '\n') {
			buffer[len - 1] = '\0';
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

int main() {
	file = fopen("test.txt", "w");
	size_t buffer_size = 8;
	char *buffer = malloc(buffer_size);
	size_t input_size = 8;
	char *input= malloc(input_size);

	if (file == NULL) {
		perror("file creation\n");
		return 1;
	}

	printf("Enter somenthing: ");
	input = readLine(input, &input_size, stdin);
	fprintf(file, "%s", input);
	printf("created a file!\n");
	fclose(file);

	file = fopen("test.txt", "r");

	buffer = readLine(buffer, &buffer_size, file);
	printf("[%s]", buffer);

	fclose(file);
	free(buffer);
	free(input);

	return 0;
}