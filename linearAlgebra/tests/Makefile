# Variables
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -fprofile-arcs -ftest-coverage
SRC_FILES = ../../test_framework/src/test_framework.c testMatrix.c ../src/matrix.c
OUTPUT = test_runner
COVERAGE_DIR = ./coverage

# Default target: Compile the tests without Valgrind and run them
all: $(OUTPUT)
	@echo "Running the tests..."
	./$(OUTPUT)

# Compile the test runner
$(OUTPUT): $(SRC_FILES)
	@echo "Compiling the latest version of the test-framework..."
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SRC_FILES)

# Clean up the compiled files
clean:
	rm -f $(OUTPUT)
	rm -f *.gcda *.gcno *.gcov

# Compile the tests, run them with Valgrind
with_valgrind: $(OUTPUT)
	valgrind --leak-check=full ./$(OUTPUT)

# Target to generate code coverage report
coverage: $(OUTPUT)
	@echo "Running tests for coverage..."
	./$(OUTPUT)
	@echo "Generating coverage report..."
	gcov -r $(SRC_FILES)
# Uncomment below if you have lcov and genhtml installed
# lcov --capture --directory . --output-file $(COVERAGE_DIR)/coverage.info
# genhtml $(COVERAGE_DIR)/coverage.info --output-directory $(COVERAGE_DIR)

# Phony targets
.PHONY: all clean with_valgrind coverage