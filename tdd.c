#include "tdd.h"

static int g_tests_run = 0;
static int g_tests_failed = 0;
static int g_assertions = 0;

int sign_of(int value)
{
    return (value > 0) - (value < 0);
}

void check_int(const char *fn, const char *case_name,
        long long expected, long long actual, int *passed)
{
    g_assertions++;
    if (expected != actual)
    {
        fprintf(stderr, "  [FAIL] %s (%s): expected %lld, got %lld\n",
                fn, case_name, expected, actual);
        *passed = 0;
    }
}

void check_size(const char *fn, const char *case_name,
        size_t expected, size_t actual, int *passed)
{
    g_assertions++;
    if (expected != actual)
    {
        fprintf(stderr, "  [FAIL] %s (%s): expected %zu, got %zu\n",
                fn, case_name, expected, actual);
        *passed = 0;
    }
}

void check_str(const char *fn, const char *case_name,
        const char *expected, const char *actual, int *passed)
{
    g_assertions++;
    if ((!expected && actual) || (expected && !actual)
        || (expected && actual && strcmp(expected, actual) != 0))
    {
        fprintf(stderr, "  [FAIL] %s (%s): expected %s%s%s, got %s%s%s\n",
                fn, case_name, expected ? "\"" : "", expected ? expected : "NULL",
                expected ? "\"" : "", actual ? "\"" : "",
                actual ? actual : "NULL", actual ? "\"" : "");
        *passed = 0;
    }
}

void check_ptr(const char *fn, const char *case_name,
        const void *expected, const void *actual, int *passed)
{
    g_assertions++;
    if (expected != actual)
    {
        fprintf(stderr, "  [FAIL] %s (%s): expected %p, got %p\n",
                fn, case_name, expected, actual);
        *passed = 0;
    }
}

void check_mem(const char *fn, const char *case_name,
        const void *expected, const void *actual, size_t size, int *passed)
{
    size_t i;
    const unsigned char *a = expected;
    const unsigned char *b = actual;

    g_assertions++;
    if (!a || !b)
    {
        if (a != b)
        {
            fprintf(stderr, "  [FAIL] %s (%s): NULL buffer\n", fn, case_name);
            *passed = 0;
        }
        return;
    }
    for (i = 0; i < size; i++)
    {
        if (a[i] != b[i])
        {
            fprintf(stderr, "  [FAIL] %s (%s): byte %zu expected 0x%02x, got 0x%02x\n",
                    fn, case_name, i, (unsigned)a[i], (unsigned)b[i]);
            *passed = 0;
            return;
        }
    }
}

void check_true(const char *fn, const char *case_name,
        int condition, int *passed)
{
    g_assertions++;
    if (!condition)
    {
        fprintf(stderr, "  [FAIL] %s (%s): condition is false\n", fn, case_name);
        *passed = 0;
    }
}

void run_test(void (*test_func)(int *), const char *name)
{
    int passed = 1;

    printf("%-22s", name);
    fflush(stdout);
    test_func(&passed);
    g_tests_run++;
    if (passed)
        printf("\033[32mPASS\033[0m\n");
    else
    {
        printf("\033[31mFAIL\033[0m\n");
        g_tests_failed++;
    }
}

int test_summary(void)
{
    printf("\nResults: %d/%d functions passed, %d assertions checked.\n",
            g_tests_run - g_tests_failed, g_tests_run, g_assertions);
    return (g_tests_failed != 0);
}
