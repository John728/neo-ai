TEST_FAIL(intentional_segfault) {
    int *p = NULL;
    *p = 42; // Dereference a null pointer to cause a segmentation fault
}