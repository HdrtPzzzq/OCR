# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 -Iinclude $(shell pkg-config --cflags sdl)
LDFLAGS =
LDLIBS = $(shell pkg-config --libs sdl)

OUT = out
SRC = $(shell find ./src -name *.c)
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

.PHONY: clean all
all: exec

exec: $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SRC) -o $(OUT) $(LDLIBS) $(LDFLAGS)

clean:
	$(RM) $(OBJ)
	$(RM) $(DEP)
	$(RM) $(OUT) $(OUT).d

-include $(DEP)
