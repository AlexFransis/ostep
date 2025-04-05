# Compiler
CC = clang

# Compiler flags
CFLAGS = -Wall -Wextra -g -arch arm64

# Output binary name
TARGET = program

# Source files
SRCS = main.c fifo.c queue.c scheduler.c task.c cpu_core.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Compile each .c file into a .o file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

