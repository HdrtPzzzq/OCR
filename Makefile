# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -Werror -std=c99 -Iinclude $(shell pkg-config --cflags sdl)
LDFLAGS =
LDLIBS = -lm $(shell pkg-config --libs sdl)

OUT = main xor img

SRC = src/main.c

IMG = $(shell find ./src/IMG -name *.c)
XOR = $(shell find ./src/XOR -name *.c)

OIMG = $(IMG:.c=.o)
OXOR = $(XOR:.c=.o)

OBJ = src/main.o $(OXOR) $(OIMG)
DEP = $(SRC:.c=.d) $(XOR:.c=.d) $(IMG:.c=.d)

.PHONY: all main XOR IMG clean
all: main

main: $(OBJ)
	$(CC) -o main $(OBJ) $(LDLIBS) $(LDFLAGS)

XOR: $(OXOR)
	$(CC) -o xor $(OXOR) $(LDLIBS) $(LDFLAGS)

IMG: $(OIMG)
	$(CC) -o img $(OIMG) $(LDLIBS) $(LDFLAGS)

clean:
	$(RM) $(OBJ)
	$(RM) $(DEP)
	$(RM) $(OUT)

-include $(DEP)
