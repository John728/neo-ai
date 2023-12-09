#include "test_framework.h"
#include <signal.h>

// Global variables
static Test *head = NULL;
static Test *tail = NULL;
static Test *current_test = NULL;

jmp_buf test_buf;
int current_test_failed_due_to_signal = 0;
Resource *resource_list = NULL;

// Signal handler for SIGSEGV and SIGABRT
void handle_sigsegv(int signum, siginfo_t *si, void *unused) {
    (void)si;
    (void)unused;

    if (signum == SIGSEGV) {
        // Program should never segfault, so this is a failure
        printf("Segmentation fault in %s", current_test->test_name);
        current_test->failed = 1;
    } else if (signum == SIGABRT) {
        // Program can abort, so this can be okay
        printf("Abort called in %s", current_test->test_name);
        current_test_failed_due_to_signal = 1;
    }
    cleanup_resources();
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
                setTextRed();
                printf(" -> FAILED (was expected to fail but didn't)\n");
                resetTextColour();
                current->failed = 1;
            } else {
                setTextGreen();
                printf(" -> PASSED\n");
                resetTextColour();
                passed++;
                
            }
        } else if (current_test_failed_due_to_signal && current->should_fail) {
            setTextGreen();
            printf(" -> PASSED (It failed as expected)\n");
            resetTextColour();
            passed++;
            current->failed = 0;
        } else {
            setTextRed();
            printf(" -> FAILED\n");
            resetTextColour();
            current->failed = 1;
        }
        
        total++;
        current = current->next;
    }

    printf("\n--- Test Summary ---\n");
    printf("Total tests: %d\n", total);
    printf("Passed: %d\n", passed);
    printf("Failed: %d\n", total - passed);
    printf("--------------------\n");
}

void printResultsToFile(char *filename) {
    FILE *file = fopen(filename, "w");

    Test *current = head;
    while (current) {
        fprintf(file, "%s,%d\n", current->test_name, current->failed);
        current = current->next;
    }

    fclose(file);
}

void setTextRed() {
    printf("\033[1;31m");
}

void setTextGreen() {
    printf("\033[0;32m");
}

void resetTextColour() {
    printf("\033[0m");
}

void add_resource_to_cleanup(void *ptr, void (*free_func)(void *)) {
    Resource *res = malloc(sizeof(Resource));
    res->ptr = ptr;
    res->free_func = free_func;
    res->next = resource_list;
    resource_list = res;
}

void cleanup_resources() {
    while (resource_list != NULL) {
        Resource *current = resource_list;
        resource_list = current->next;
        current->free_func(current->ptr);
        free(current);
    }
}