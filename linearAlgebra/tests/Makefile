# Variables
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g
SRC_FILES = ../../test_framework/src/test_framework.c test_matrix.c ../src/matrix.c
OUTPUT = test_runner

# Default target: Compile the tests without Valgrind and run them
all: $(OUTPUT)
	./$(OUTPUT)

# Compile the test runner
$(OUTPUT): $(SRC_FILES)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SRC_FILES)

# Clean up the compiled files
clean:
	rm -f $(OUTPUT)

# Compile the tests, run them with Valgrind
with_valgrind: $(OUTPUT)
	valgrind --leak-check=full ./$(OUTPUT)

# Phony targets
.PHONY: all clean with_valgrind
