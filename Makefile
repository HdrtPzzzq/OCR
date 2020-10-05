# Makefile

CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 $(pkg-config --cflags sdl)
LDFLAGS =
LDLIBS = $(pkg-config --libs sdl)

SRC = $(shell find ./src -name *.c)
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: main

main: ${OBJ}
	$(CC) $(CFLAGS) $(SRC) -o main

.PHONY: clean
clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} main

-include ${DEP}
