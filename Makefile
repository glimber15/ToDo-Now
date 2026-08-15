CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -Iinclude
LDLIBS = -lsqlite3
PREFIX = $(HOME)/.local
BINDIR = $(PREFIX)/bin

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

all: tsk

tsk: $(OBJ)
	$(CC) $(OBJ) -o tsk $(LDLIBS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: tsk
	./tsk

install:
	mkdir -p $(BINDIR)
	cp tsk $(BINDIR)

uninstall:
	rm -f $(BINDIR)/tsk

clean:
	rm -f tsk $(OBJ) compile_commands.json

.PHONY: all run install uninstall clean
