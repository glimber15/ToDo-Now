CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -Iinclude

SRC = main.c $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

app: $(OBJ)
	$(CC) $(OBJ) -o app

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) app