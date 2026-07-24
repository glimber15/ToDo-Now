#include <stdio.h>

void greetUser() {
	printf("\n*********************\n");
	printf("TODO CLI by GasSpace");
	printf("\n*********************\n");
}

void createTask();
void toggleTask();
void editTask();
void deleteTask();
void clearData();

int main() {
	greetUser();

	FILE* file = fopen("task.txt", "w");
	char data[100];
	if (file == NULL) {
		printf("ERROR! : No file detected\n");
		return 0;
	}
	printf("File created successfully!\n");
	fputs("Some tasks for you boiiii\n", file);
	printf("written to file\n");

	fclose(file);

	file = fopen("task.txt", "r");
	if (file == NULL) {
		printf("ERROR! : No file detected\n");
		return 0;
	}
	printf("Contents of file:\n");
	while(fgets(data, 100, file)) {
		printf("%s", data);
	}

	fclose(file);

	return 0;
}