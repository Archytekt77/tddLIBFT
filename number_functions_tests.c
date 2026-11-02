#include "tdd.h"

void test_ft_atoi(int *passed)
{
    static const char *const cases[] = {
        "0", "42", "-42", "+42", "  -123", "\t\n\v\f\r 321",
        "00042", "--42", "+-42", "42andmore", "", "     ",
        "2147483647", "-2147483648", "1 2", "-0", NULL
    };
    size_t i;

    for (i = 0; cases[i]; i++)
        CHECK_INT("ft_atoi", cases[i], atoi(cases[i]), ft_atoi(cases[i]));
    /* Overflow values intentionally excluded: atoi overflow is undefined. */
}

void test_ft_itoa(int *passed)
{
    static const int cases[] = {
        0, 1, -1, 42, -42, 1000000, INT_MAX, INT_MIN
    };
    size_t i;
    char expected[32];
    char *actual;

    for (i = 0; i < sizeof(cases) / sizeof(cases[0]); i++)
    {
        snprintf(expected, sizeof(expected), "%d", cases[i]);
        actual = ft_itoa(cases[i]);
        CHECK_STR("ft_itoa", expected, expected, actual);
        free(actual);
    }
}
