CC=gcc
CFLAGS=-Wall -Wextra -Werror -pedantic -std=c99

OBJDIR = obj
BINDIR = bin

DIRS = $(shell find algorithms data-structures -type d)

SRCS = $(foreach dir,$(filter-out $(foreach dir,$(DIRS),$(if $(wildcard $(dir)/*.c),,$(dir))),$(DIRS)), $(wildcard $(dir)/*.c))
OBJS = $(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.o)))

.PHONY: all test clean

all: $(OBJDIR) $(OBJS) $(BINDIR)
	$(CC) $(CFLAGS) $(OBJS) test.c -o $(BINDIR)/test -lcriterion

test:
	docker build -t test .
	docker run -it --rm test

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)
	docker rmi test

$(OBJDIR)/%.o: $(SRCS)
	$(CC) $(CFLAGS) -c $(filter %/$*.c,$(SRCS)) -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

$(BINDIR):
	mkdir $(BINDIR)
