# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 $(shell pkg-config --cflags sdl) -Iinclude
LDFLAGS =
LDLIBS = $(shell pkg-config --libs sdl)

SRC = $(shell find ./src -name *.c)
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: main

main: ${OBJ}
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(SRC) -o main $(LDLIBS)

.PHONY: clean
clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} main
	${RM} main.d

-include ${DEP}
