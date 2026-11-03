#include "tdd.h"

void test_ft_memset(int *passed)
{
    unsigned char b[12];
    unsigned char expected[12];

    memset(b, 'x', sizeof(b));
    memset(expected, 'x', sizeof(expected));
    CHECK_PTR("ft_memset", "return", b + 2, ft_memset(b + 2, 'A', 5));
    memset(expected + 2, 'A', 5);
    CHECK_MEM("ft_memset", "partial", expected, b, sizeof(b));
    ft_memset(b, 0x123, 2);
    memset(expected, 0x23, 2);
    CHECK_MEM("ft_memset", "unsigned char cast", expected, b, sizeof(b));
    ft_memset(b, 'Q', 0);
    CHECK_MEM("ft_memset", "zero length", expected, b, sizeof(b));
}

void test_ft_bzero(int *passed)
{
    unsigned char b[12];
    unsigned char expected[12];

    memset(b, 'x', sizeof(b));
    memset(expected, 'x', sizeof(expected));
    ft_bzero(b + 2, 5);
    memset(expected + 2, 0, 5);
    CHECK_MEM("ft_bzero", "partial", expected, b, sizeof(b));
    ft_bzero(b, 0);
    CHECK_MEM("ft_bzero", "zero length", expected, b, sizeof(b));
}

void test_ft_memcpy(int *passed)
{
    unsigned char src[] = {0, 1, 2, 3, 0, 255};
    unsigned char dst[8];
    unsigned char expected[8];

    memset(dst, 0xaa, sizeof(dst));
    memset(expected, 0xaa, sizeof(expected));
    CHECK_PTR("ft_memcpy", "return", dst, ft_memcpy(dst, src, sizeof(src)));
    memcpy(expected, src, sizeof(src));
    CHECK_MEM("ft_memcpy", "binary data", expected, dst, sizeof(dst));
    CHECK_PTR("ft_memcpy", "zero return", dst, ft_memcpy(dst, src, 0));
    CHECK_MEM("ft_memcpy", "zero length", expected, dst, sizeof(dst));
}

void test_ft_memmove(int *passed)
{
    char buf1[16] = "abcdefghij";
    char buf2[16] = "abcdefghij";
    char buf3[16] = "abcdefghij";
    char buf4[16] = "abcdefghij";

    CHECK_PTR("ft_memmove", "forward overlap return", buf1 + 2,
            ft_memmove(buf1 + 2, buf1, 7));
    memmove(buf2 + 2, buf2, 7);
    CHECK_MEM("ft_memmove", "forward overlap", buf2, buf1, sizeof(buf1));
    CHECK_PTR("ft_memmove", "backward overlap return", buf3,
            ft_memmove(buf3, buf3 + 2, 7));
    memmove(buf4, buf4 + 2, 7);
    CHECK_MEM("ft_memmove", "backward overlap", buf4, buf3, sizeof(buf3));
    CHECK_PTR("ft_memmove", "zero return", buf3, ft_memmove(buf3, buf3, 0));
}

void test_ft_memchr(int *passed)
{
    const unsigned char b[] = {0, 1, 2, 3, 0, 255};

    CHECK_PTR("ft_memchr", "first NUL", b, ft_memchr(b, 0, 6));
    CHECK_PTR("ft_memchr", "binary 255", b + 5, ft_memchr(b, 255, 6));
    CHECK_PTR("ft_memchr", "unsigned c", b + 5, ft_memchr(b, 511, 6));
    CHECK_PTR("ft_memchr", "limited length", NULL, ft_memchr(b, 255, 5));
    CHECK_PTR("ft_memchr", "not found", NULL, ft_memchr(b, 42, 6));
    CHECK_PTR("ft_memchr", "zero length", NULL, ft_memchr(b, 0, 0));
}

static void compare_memcmp(const char *label, const void *a,
        const void *b, size_t n, int *passed)
{
    CHECK_INT("ft_memcmp", label,
            sign_of(memcmp(a, b, n)), sign_of(ft_memcmp(a, b, n)));
}

void test_ft_memcmp(int *passed)
{
    const unsigned char a[] = {1, 2, 3, 0, 255};
    const unsigned char b[] = {1, 2, 4, 0, 255};
    const unsigned char c[] = {1, 2, 3, 0, 0};

    compare_memcmp("equal", a, a, sizeof(a), passed);
    compare_memcmp("less", a, b, sizeof(a), passed);
    compare_memcmp("greater", b, a, sizeof(a), passed);
    compare_memcmp("prefix", a, b, 2, passed);
    compare_memcmp("zero length", a, b, 0, passed);
    compare_memcmp("after NUL", a, c, sizeof(a), passed);
}

void test_ft_calloc(int *passed)
{
    unsigned char *p;
    size_t i;
    int all_zero;

    p = ft_calloc(32, sizeof(int));
    CHECK_TRUE("ft_calloc", "allocation", p != NULL);
    if (p)
    {
        all_zero = 1;
        for (i = 0; i < 32 * sizeof(int); i++)
            if (p[i] != 0)
                all_zero = 0;
        CHECK_TRUE("ft_calloc", "zeroed bytes", all_zero);
        free(p);
    }
    /* Subject v19.3 requires a non-NULL, freeable pointer for zero sizes. */
    p = ft_calloc(0, 8);
    CHECK_TRUE("ft_calloc", "zero count allocation", p != NULL);
    free(p);
    p = ft_calloc(8, 0);
    CHECK_TRUE("ft_calloc", "zero size allocation", p != NULL);
    free(p);
    p = ft_calloc(0, 0);
    CHECK_TRUE("ft_calloc", "both zero allocation", p != NULL);
    free(p);
    p = ft_calloc(SIZE_MAX, 2);
    CHECK_PTR("ft_calloc", "multiplication overflow", NULL, p);
    free(p);
}
