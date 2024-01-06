# Variables
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -fprofile-arcs -ftest-coverage
SRC_FILES = ./main.c ./imageProcessing/src/imageProcessing.c ./linearAlgebra/src/matrix.c ./neuralNerwork/src/neuralNetwork.c
OUTPUT = main
COVERAGE_DIR = ./coverage

# Default target: Compile the tests without Valgrind and run them
all: $(OUTPUT)
	@echo "Running main"
	./$(OUTPUT)

# Compile the test runner
$(OUTPUT): $(SRC_FILES)
	@echo "Cleaning up files"
	rm -f $(OUTPUT)
	rm -f *.gcda *.gcno *.gcov
	@echo "Compiling the latest version of main"
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SRC_FILES) -lm

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