#include <stdio.h>

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

int main() {
	printH("Hello0", '#');

	return 0;
}