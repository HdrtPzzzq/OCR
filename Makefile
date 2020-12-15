# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -Werror -std=c99 -g -Iinclude $(shell pkg-config --cflags sdl) $(shell pkg-config --cflags gtk+-3.0)
LDFLAGS =
LDLIBS = -lm $(shell pkg-config --libs sdl ) $(shell pkg-config --libs gtk+-3.0)

OUT = net interface

NET = $(shell find ./src/NET -name *.c)
INTERFACE = $(shell find ./src/INTERFACE -name *.c)

ONET = $(NET:.c=.o)
OINTERFACE = $(INTERFACE:.c=.o)

AOBJ = $(ONET) $(OINTERFACE)

DEP = $(NET:.c=.d) $(INTERFACE:.c=.d)

.PHONY: all NET INTERFACE clean

all: NET INTERFACE

NET: $(ONET)
	$(CC) -o net $(ONET) $(LDLIBS) $(LDFLAGS)

INTERFACE: $(OINTERFACE)
	$(CC) -o interface $(OINTERFACE) $(LDLIBS) $(LDFLAGS)

clean:
	$(RM) $(AOBJ)
	$(RM) $(DEP)
	$(RM) $(OUT)

-include $(DEP)
