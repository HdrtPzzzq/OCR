# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -Werror -std=c99 -Iinclude $(shell pkg-config --cflags sdl)
LDFLAGS =
LDLIBS = $(shell pkg-config --libs sdl)

OUT = main
SRC = $(shell find ./src -name *.c)
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

.PHONY: clean all
all: exec

exec: $(OBJ)
	$(CC) -o $(OUT) $(OBJ) $(LDLIBS) $(LDFLAGS)

clean:
	$(RM) $(OBJ)
	$(RM) $(DEP)
	$(RM) $(OUT)

-include $(DEP)
