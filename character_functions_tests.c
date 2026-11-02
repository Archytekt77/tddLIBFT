#include "tdd.h"
#include <ctype.h>

/* ctype functions accept EOF or unsigned char values only. */
#define CHECK_CLASSIFICATION(test_name, libc_fn, ft_fn)                 \
    do {                                                               \
        int c;                                                         \
        char label[32];                                                \
        for (c = 0; c <= UCHAR_MAX; c++) {                             \
            snprintf(label, sizeof(label), "character %d", c);        \
            CHECK_INT((test_name), label, (libc_fn(c) != 0), (ft_fn(c) != 0)); \
        }                                                              \
        CHECK_INT((test_name), "EOF", (libc_fn(EOF) != 0), (ft_fn(EOF) != 0)); \
    } while (0)

void test_ft_isalpha(int *passed)
{
    CHECK_CLASSIFICATION("ft_isalpha", isalpha, ft_isalpha);
}

void test_ft_isdigit(int *passed)
{
    CHECK_CLASSIFICATION("ft_isdigit", isdigit, ft_isdigit);
}

void test_ft_isalnum(int *passed)
{
    CHECK_CLASSIFICATION("ft_isalnum", isalnum, ft_isalnum);
}

void test_ft_isascii(int *passed)
{
    int c;
    char label[32];

    for (c = -1; c <= UCHAR_MAX; c++)
    {
        snprintf(label, sizeof(label), "character %d", c);
        CHECK_INT("ft_isascii", label, (c >= 0 && c <= 127), (ft_isascii(c) != 0));
    }
}

void test_ft_isprint(int *passed)
{
    CHECK_CLASSIFICATION("ft_isprint", isprint, ft_isprint);
}

void test_ft_toupper(int *passed)
{
    int c;
    char label[32];

    for (c = -1; c <= UCHAR_MAX; c++)
    {
        snprintf(label, sizeof(label), "character %d", c);
        CHECK_INT("ft_toupper", label, toupper(c), ft_toupper(c));
    }
}

void test_ft_tolower(int *passed)
{
    int c;
    char label[32];

    for (c = -1; c <= UCHAR_MAX; c++)
    {
        snprintf(label, sizeof(label), "character %d", c);
        CHECK_INT("ft_tolower", label, tolower(c), ft_tolower(c));
    }
}
