# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -Werror -g -O0 -std=c99 -Iinclude $(shell pkg-config --cflags sdl)
LDFLAGS =
LDLIBS = -lm $(shell pkg-config --libs sdl)

OUT = main xor img seg

SRC =

IMG = $(shell find ./src/IMG -name *.c)
XOR = $(shell find ./src/XOR -name *.c)

OBJ = $(SRC:.c=.o)

OIMG = $(IMG:.c=.o)
OXOR = $(XOR:.c=.o)

AOBJ = $(OBJ) $(OIMG) $(OXOR)
DEP = $(SRC:.c=.d) $(IMG:.c=.d) $(XOR:.c=.d)

.PHONY: all main XOR IMG clean
all: IMG XOR

IMG: $(OIMG)
	$(CC) -o img $(OIMG) $(LDLIBS) $(LDFLAGS)

XOR: $(OXOR)
	$(CC) -o xor $(OXOR) $(LDLIBS) $(LDFLAGS)

clean:
	$(RM) $(AOBJ)
	$(RM) $(DEP)
	$(RM) $(OUT)

-include $(DEP)
