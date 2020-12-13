# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -Werror -std=c99 -Iinclude $(shell pkg-config --cflags sdl) $(shell pkg-config --cflags gtk+-3.0)
LDFLAGS =
LDLIBS = -lm $(shell pkg-config --libs sdl ) $(shell pkg-config --libs gtk+-3.0)

OUT = main xor img interface

SRC =

IMG = $(shell find ./src/IMG -name *.c)
XOR = $(shell find ./src/XOR -name *.c)
INTERFACE = $(shell find ./src/INTERFACE -name *.c)

OBJ = $(SRC:.c=.o)

OIMG = $(IMG:.c=.o)
OXOR = $(XOR:.c=.o)
OINTERFACE = $(INTERFACE:.c=.o)

AOBJ = $(OBJ) $(OIMG) $(OXOR) $(OINTERFACE)

DEP = $(SRC:.c=.d) $(IMG:.c=.d) $(XOR:.c=.d) $(INTERFACE:.c=.d)

.PHONY: all main XOR IMG INTERFACE clean

all: IMG XOR INTERFACE

IMG: $(OIMG)
	$(CC) -o img $(OIMG) $(LDLIBS) $(LDFLAGS)

XOR: $(OXOR)
	$(CC) -o xor $(OXOR) $(LDLIBS) $(LDFLAGS)

INTERFACE: $(OINTERFACE)
	$(CC) -o interface $(OINTERFACE) $(LDLIBS) $(LDFLAGS)

clean:
	$(RM) $(AOBJ)
	$(RM) $(DEP)
	$(RM) $(OUT)

-include $(DEP)
