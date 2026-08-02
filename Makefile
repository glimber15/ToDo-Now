CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -Iinclude

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

.PHONY: all run clean

all: task

task: $(OBJ)
	$(CC) $(OBJ) -o task

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: task
	./task

clean:
	rm -f task $(OBJ) compile_commands.json