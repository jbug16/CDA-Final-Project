CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = BinaryInt
OBJS = BinaryInt.o

# Default rule
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile source files
BinaryInt.o: BinaryInt.c BinaryInt.h
	$(CC) $(CFLAGS) -c BinaryInt.c

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)