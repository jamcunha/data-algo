CC=gcc
CFLAGS=-Wall -Wextra -Werror -pedantic -std=c99

OBJDIR = obj
BIN = bin

SRCS = $(wildcard */*.c)
OBJS = $(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.o)))

.PHONY: all test clean

all: $(OBJDIR) $(OBJS) $(BIN)
	$(CC) $(CFLAGS) $(OBJS) test.c -o ./bin/test -lcriterion

test:
	docker build -t test .
	docker run -it --rm test

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BIN)
	docker rmi test

$(OBJDIR)/%.o: */%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

$(BIN):
	mkdir $(BIN)
