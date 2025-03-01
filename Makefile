# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS = -lSDL2

# Source files
SRCS = main.c memory.c cpu.c display.c input.c
OBJS = $(SRCS:.c=.o)
EXEC = bytepusher

# Default target
all: $(EXEC)

# Link object files to create executable
$(EXEC): $(OBJS)
	$(CC) -o $(EXEC) $(OBJS) $(LDFLAGS)

# Compile source files to object files
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

# Special case for main.o which depends on multiple headers
main.o: main.c memory.h cpu.h display.h input.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJS) $(EXEC)

# Run target
run: $(EXEC)
	./$(EXEC) $(ROM)

# Phony targets
.PHONY: all clean run