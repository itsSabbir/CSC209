##
# kar - CSC209H1F archive manager
#
# @file
# @version 0.1

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Source files
SRCS = kar.c kar_tree.c archive.c extract.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = kar

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)


# end
