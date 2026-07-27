#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *file;

int main() {
	char *str = "Hello There";
	size_t size = strlen(str);
	file = fopen("test.bin", "wb");

	if (file == NULL) {
		perror("file creation");
		return 1;
	}
	size_t written = fwrite(str, sizeof(char), size, file);
	if (written != size) {
		perror("file writing");
		return 1;
	}
	printf("file writting successfull!");

	fclose(file);

	return 0;
}