// test_framework.h

#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

typedef void (*test_fn)();

extern int current_test_failed_due_to_signal;

typedef struct Test {
    const char *test_name;
    const int should_fail;
    int failed;
    test_fn func;
    struct Test *next;
} Test;

#define TEST(name) \
    void name(); \
    static Test __test_##name = { .test_name = #name, .func = name, .next = NULL }; \
    static __attribute__((constructor)) void __reg_##name() { register_test(&__test_##name); } \
    void name()

#define TEST_FAIL(name) \
    void name(); \
    static Test __test_##name = { .test_name = #name, .func = name, .should_fail = 1, .next = NULL }; \
    static __attribute__((constructor)) void __reg_##name() { register_test(&__test_##name); } \
    void name()

void register_test(Test *test);
void run_tests();

extern jmp_buf test_buf;

#define ASSERT(expr) \
    do { \
        if (!(expr)) { \
            printf("FAIL (line %d: %s)", __LINE__, #expr); \
            longjmp(test_buf, 1); \
        } \
    } while (0)

#endif // TEST_FRAMEWORK_H


void setTextRed();
void setTextGreen();
void resetTextColour();