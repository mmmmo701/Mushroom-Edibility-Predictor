# Compiler and defaults
CC := gcc
CFLAGS := -Wall -Wextra -std=c11
LDFLAGS :=
INCLUDES := -I.

# Source discovery
HEADERS := $(wildcard *.h)
SRCS_ALL := $(wildcard *.c)

# Modes can be space-separated (e.g., "test debug")
MODES ?= normal

# Base config
SRCS := $(SRCS_ALL)
TARGET := prog

# Apply mode-specific rules
ifneq (,$(filter test,$(MODES)))
SRCS := $(filter-out main.c,$(SRCS))
TARGET := testprog
endif

ifneq (,$(filter debug,$(MODES)))
CFLAGS += -DDEBUG -g
endif

OBJS := $(SRCS:.c=.o)

.PHONY: all test debug clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

# Convenience targets
test:
	$(MAKE) MODES="test"

debug:
	$(MAKE) MODES="debug"

test-debug:
	$(MAKE) MODES="test debug"

clean:
	rm -f $(OBJS) prog testprog