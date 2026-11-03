#include "tdd.h"
#ifndef _WIN32
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
#endif

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
#ifndef _WIN32
    int fd[2];
    int report[2];
    int status;
    pid_t child;
    pid_t waited;
#endif

    g_tests_run++;
#ifndef _WIN32
    fflush(NULL);
    if (pipe(fd) != 0)
    {
        perror("pipe du testeur");
        g_tests_failed++;
        return;
    }
    child = fork();
    if (child == 0)
    {
        close(fd[0]);
        alarm(3);
        g_assertions = 0;
        test_func(&passed);
        report[0] = passed;
        report[1] = g_assertions;
        if (write(fd[1], report, sizeof(report)) != (ssize_t)sizeof(report))
            passed = 0;
        close(fd[1]);
        fflush(NULL);
        _exit(!passed);
    }
    close(fd[1]);
    if (child < 0)
    {
        close(fd[0]);
        perror("fork du testeur");
        g_tests_failed++;
        return;
    }
    do {
        waited = waitpid(child, &status, 0);
    } while (waited < 0 && errno == EINTR);
    if (waited < 0)
    {
        close(fd[0]);
        perror("waitpid du testeur");
        g_tests_failed++;
        return;
    }
    if (WIFSIGNALED(status))
    {
        close(fd[0]);
        printf("%-22s%s (signal %d)\n", name,
                WTERMSIG(status) == SIGALRM ? "TIMEOUT" : "CRASH",
                WTERMSIG(status));
        g_tests_failed++;
        return;
    }
    passed = 0;
    if (read(fd[0], report, sizeof(report)) == (ssize_t)sizeof(report))
    {
        passed = report[0] && WIFEXITED(status) && WEXITSTATUS(status) == 0;
        g_assertions += report[1];
    }
    close(fd[0]);
#else
    test_func(&passed);
#endif
    printf("%-22s", name);
    if (passed)
        printf("OK\n");
    else
    {
        printf("KO\n");
        g_tests_failed++;
    }
}

int test_summary(void)
{
    printf("\nBilan : %d/%d fonctions OK, %d verifications effectuees.\n",
            g_tests_run - g_tests_failed, g_tests_run, g_assertions);
    return (g_tests_failed != 0);
}
