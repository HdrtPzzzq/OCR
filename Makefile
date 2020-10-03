# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC = src/main.c src/loadbm.c
OBJ = ${SRC:.c=.o}

all: ${OBJ}
	$(CC) $(CFLAGS) $(SRC) -o main
clean:
	${RM} ${OBJ}
	${RM} main
