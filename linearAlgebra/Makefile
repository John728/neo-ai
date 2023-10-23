# Compiler and flags
CC = gcc
CFLAGS = -Wall

# Directories
SRC_DIR = src
TESTS_DIR = tests

# Source and object files
SRC_FILES = $(SRC_DIR)/matrix.c
OBJ_FILES = $(SRC_FILES:.c=.o)
TEST_FILES = $(TESTS_DIR)/test_matrix.c $(TESTS_DIR)/test.c
TEST_OBJ_FILES = $(TEST_FILES:.c=.o)

# Targets
all: program tests

program: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(SRC_DIR)/a.out $(OBJ_FILES)

tests: $(OBJ_FILES) $(TEST_OBJ_FILES)
	$(CC) $(CFLAGS) -o $(TESTS_DIR)/a.out $(OBJ_FILES) $(TEST_OBJ_FILES)

# Generic rule for .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o $(TESTS_DIR)/*.o $(SRC_DIR)/a.out $(TESTS_DIR)/a.out
