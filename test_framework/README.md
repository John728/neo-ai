## Set up

1. Inlcude the test framework inside test file
2. Each test case stats with: 
```
TEST(test_name) {
    // ... code
}
```

3. Each test file needs to end with :
```
int main() {
    run_tests();
    return 0;
}
```
which runs the tests.

4. Options:
```
ASSERT(/*statement*/);
TEST_FAIL(...) {...}
```
5. Boilerplate makefile text for make commands (!will fix later):
```
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
```


Note:

If you expect a test to fail, you can register a recourse you want to clean up after the test is complete with the 

REGISTER_RESOURCE_FOR_CLEANUP(recourse, clean_up_function);

which will be called after the function, and will apply the clean up function to the resourse. You do not have to use this if you do not expect a function to fail. Do not manually free if you use this.


OTHER TOOLS:


GDB + GDBGUI can be very useful in finding bugs
valgrind is very usefull in finding memleaks
gcov -n -o . test_runner-testMatrix.gcno