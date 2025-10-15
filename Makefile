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
else
SRCS := $(filter-out test.c,$(SRCS))
endif

ifneq (,$(filter debug,$(MODES)))
CFLAGS := $(CFLAGS) -DDEBUG -g
endif

ifneq (,$(filter debug-2,$(MODES)))
CFLAGS := $(CFLAGS) -DDEBUG_2 -g
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

debug-2:
	$(MAKE) MODES="debug-2"

test-debug:
	$(MAKE) MODES="test debug"

clean:
	rm -f $(OBJS) prog testprog