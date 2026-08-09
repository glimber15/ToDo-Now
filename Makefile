CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -Iinclude
LDLIBS = -lsqlite3

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

.PHONY: all run clean

all: tsk

tsk: $(OBJ)
	$(CC) $(OBJ) -o tsk $(LDLIBS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: tsk
	./tsk

clean:
	rm -f tsk $(OBJ) compile_commands.json
