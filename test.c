#include <stdio.h>

void message(char *text) {
	printf("%s\n", text);
}
void changeName(char *name) {
	name = "Thara";
}

int main() {
	char *name = "Surya";
	message("Hello There!!");
	changeName(name);
	printf("%s", name);

	return 0;
}