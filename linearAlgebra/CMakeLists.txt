# COMMENT "Building and running tests..."

# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(TestRunner)

# Compiler and flags
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -g")

# Source files
set(SRC_FILES 
    ../test_framework/src/test_framework.c 
    ../tests/testMatrix.c 
    ../src/matrix.c
)

# Create an executable from the source files
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Custom target to run tests after building
add_custom_target(run_tests 
    COMMAND ${PROJECT_NAME}
    COMMENT "Running the tests..."
    DEPENDS ${PROJECT_NAME}
    VERBATIM
)

# Custom target to run tests with Valgrind
find_program(VALGRIND "valgrind")
if(VALGRIND)
    add_custom_target(with_valgrind
        COMMAND ${VALGRIND} --leak-check=full ./${PROJECT_NAME}
        COMMENT "Running the tests with Valgrind..."
        DEPENDS ${PROJECT_NAME}
        VERBATIM
    )
else()
    message(WARNING "Valgrind not found! 'with_valgrind' target will not be available.")
endif()