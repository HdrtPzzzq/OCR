# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -Werror -std=c99 -Iinclude $(shell pkg-config --cflags sdl)
LDFLAGS =
LDLIBS = -lm $(shell pkg-config --libs sdl)

OUT = main xor img seg

SRC =

IMG = $(shell find ./src/IMG -name *.c)
SEG = $(shell find ./src/SEG -name *.c)
XOR = $(shell find ./src/XOR -name *.c)

OBJ = $(SRC:.c=.o)

OIMG = $(IMG:.c=.o)
OSEG = $(SEG:.c=.o)
OXOR = $(XOR:.c=.o)

AOBJ = $(OBJ) $(OIMG) $(OSEG) $(OXOR)
DEP = $(SRC:.c=.d) $(IMG:.c=.d) $(SEG:.c=.d) $(XOR:.c=.d)

.PHONY: all main XOR IMG clean
all: main

main: $(AOBJ)
	$(CC) -o main $(AOBJ) $(LDLIBS) $(LDFLAGS)

IMG: $(OIMG)
	$(CC) -o img $(OIMG) $(LDLIBS) $(LDFLAGS)

SEG: $(OSEG)
	$(CC) -o seg $(OSEG) $(LDLIBS) $(LDFLAGS)

XOR: $(OXOR)
	$(CC) -o xor $(OXOR) $(LDLIBS) $(LDFLAGS)

clean:
	$(RM) $(AOBJ)
	$(RM) $(DEP)
	$(RM) $(OUT)

-include $(DEP)
