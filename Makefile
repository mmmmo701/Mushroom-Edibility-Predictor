# Makefile - build modes: normal (default) or test; DEBUG adds -DDEBUG and -g
CC := gcc
CFLAGS := -Wall -Wextra -std=c11
LDFLAGS :=
INCLUDES := -I.

MODE ?= normal
HEADERS := $(wildcard *.h)
SRCS_ALL := $(wildcard *.c)

ifeq ($(MODE),test)
SRCS := $(filter-out main.c,$(SRCS_ALL))
else
SRCS := $(filter-out test.c,$(SRCS_ALL))
endif

OBJS := $(SRCS:.c=.o)
TARGET := $(if $(filter test,$(MODE)),testprog,prog)

ifdef DEBUG
CFLAGS += -DDEBUG -g
endif

.PHONY: all test debug clean
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# every object depends on all headers so header changes trigger rebuilds
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

# convenience targets
test:
	$(MAKE) MODE=test

debug:
	$(MAKE) DEBUG=1

clean:
	rm -f $(OBJS) $(TARGET)