#include "test_framework.h"
#include <signal.h>

// Global variables
static Test *head = NULL;
static Test *tail = NULL;
static int failed_due_to_segfault = 0;
static Test *current_test = NULL;

jmp_buf test_buf;

// Signal handler for SIGSEGV
void handle_sigsegv(int signum) {
    (void) signum;  // Unused parameter
    printf("FAIL (Segmentation fault in %s)\n", current_test->test_name);
    failed_due_to_segfault = 1;
    longjmp(test_buf, 1);
}

void register_test(Test *test) {
    if (tail == NULL) {
        head = tail = test;
    } else {
        tail->next = test;
        tail = test;
    }
}

void run_tests() {

    int passed = 0;
    int total = 0;

    signal(SIGSEGV, handle_sigsegv); // Register the signal handler
    Test *current = head;

    while (current) {

        printf("Running test: %s... ", current->test_name);
        
        // Reset the flag for next tests
        if (failed_due_to_segfault) {
            failed_due_to_segfault = 0;  
        }

        if (!setjmp(test_buf)) {
            current_test = current;
            current->func();
            printf("PASSED\n");
            passed++;
        }
        
        total++;
        current = current->next;
    }

    printf("\n--- Test Summary ---\n");
    printf("Total tests: %d\n", total);
    printf("Passed: %d\n", passed);
    printf("Failed: %d\n", total - passed);
}
