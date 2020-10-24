# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -Werror -std=c99 -Iinclude $(shell pkg-config --cflags sdl)
LDFLAGS =
LDLIBS = $(shell pkg-config --libs sdl)

OUT = main xor
SRC = $(shell find ./src -name *.c)
XOR = $(shell find ./XOR -name *.c)
OXOR = $(XOR:.c=.o)
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d) $(XOR:.c=.d)

.PHONY: clean all
all: main

XOR: $(OXOR)
	$(CC) -o xor $(OXOR) -lm

main: $(OBJ)
	$(CC) -o main $(OBJ) $(LDLIBS) $(LDFLAGS)

clean:
	$(RM) $(OBJ) $(OXOR)
	$(RM) $(DEP)
	$(RM) $(OUT)

-include $(DEP)
