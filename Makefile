CC=gcc
CFLAGS=-Wall -Wextra -Werror -pedantic -std=c99

OBJDIR = obj
BINDIR = bin

DIRS = $(shell find algorithms data-structures -type d)

SRCS = $(foreach dir,$(filter-out $(foreach dir,$(DIRS),$(if $(wildcard $(dir)/*.c),,$(dir))),$(DIRS)), $(wildcard $(dir)/*.c))
OBJS = $(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.o)))

TEST_SRCS = $(wildcard tests/*.c)
TEST_BINS = $(patsubst tests/%_test.c,$(BINDIR)/%,$(TEST_SRCS))

.PHONY: all test clean docker

all: $(OBJDIR) $(BINDIR) $(OBJS) $(TEST_BINS)

test: all
	@for test in $(TEST_BINS); do ./$$test; done

docker:
	docker build -t test .
	docker run -it --rm test

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)
	docker rmi test

$(BINDIR)/%: $(OBJDIR)/%.o
	$(CC) $(CFLAGS) $< tests/$*_test.c -o $@ -lcriterion

$(OBJDIR)/%.o: $(SRCS)
	$(CC) $(CFLAGS) -c $(filter %/$*.c,$(SRCS)) -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

$(BINDIR):
	mkdir $(BINDIR)
