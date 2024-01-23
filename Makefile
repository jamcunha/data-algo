CC=gcc
CFLAGS=-Wall -Wextra -Werror -pedantic -std=c99

all: test

test: test.c
	$(CC) $(CFLAGS) -o test test.c -lcriterion
