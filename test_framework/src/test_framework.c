#include "test_framework.h"
#include <signal.h>

// Global variables
static Test *head = NULL;
static Test *tail = NULL;
static Test *current_test = NULL;

jmp_buf test_buf;
int current_test_failed_due_to_signal = 0;

// Signal handler for SIGSEGV and SIGABRT
void handle_sigsegv(int signum, siginfo_t *si, void *unused) {
    (void)si;
    (void)unused;

    if (signum == SIGSEGV) {
        // Program should never segfault, so this is a failure
        printf("Segmentation fault in %s", current_test->test_name);
    } else if (signum == SIGABRT) {
        // Program can abort, so this can be okay
        printf("Abort called in %s", current_test->test_name);
        current_test_failed_due_to_signal = 1;
    }

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
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_sigsegv;

    sigaction(SIGSEGV, &sa, NULL);
    sigaction(SIGABRT, &sa, NULL);

    int passed = 0;
    int total = 0;
    Test *current = head;

    while (current) {
        printf("Running test: %s... ", current->test_name);
        
        current_test_failed_due_to_signal = 0;
        current_test = current;

        if (!setjmp(test_buf)) {
            current->func();

            if (current->should_fail) {
                printf(" -> FAILED (was expected to fail but didn't)\n");
            } else {
                printf(" -> PASSED\n");
                passed++;
            }
        } else if (current_test_failed_due_to_signal && current->should_fail) {
            printf(" -> PASSED (It failed as expected)\n");
            passed++;
        } else {
            printf(" -> FAILED\n");
        }
        
        total++;
        current = current->next;
    }

    printf("\n--- Test Summary ---\n");
    printf("Total tests: %d\n", total);
    printf("Passed: %d\n", passed);
    printf("Failed: %d\n", total - passed);
}

void printResultsToFile(char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error: Could not open file %s for writing.\n", filename);
        abort();
    }

    Test *current = head;
    while (current) {
        fprintf(fp, "%s,%d\n", current->test_name, current->should_fail);
        current = current->next;
    }

    fclose(fp);
}