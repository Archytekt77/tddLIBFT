#include "tdd.h"

static void check_owned_string(const char *fn, const char *label,
        const char *expected, char *actual, int *passed)
{
    CHECK_STR(fn, label, expected, actual);
    free(actual);
}

void test_ft_strlen(int *passed)
{
    CHECK_SIZE("ft_strlen", "empty", 0, ft_strlen(""));
    CHECK_SIZE("ft_strlen", "Hello", 5, ft_strlen("Hello"));
    CHECK_SIZE("ft_strlen", "embedded NUL", 3, ft_strlen("abc\0def"));
    CHECK_SIZE("ft_strlen", "spaces", 4, ft_strlen("    "));
}

void test_ft_strchr(int *passed)
{
    const char s[] = "Hello";

    CHECK_PTR("ft_strchr", "first", s, ft_strchr(s, 'H'));
    CHECK_PTR("ft_strchr", "middle", s + 2, ft_strchr(s, 'l'));
    CHECK_PTR("ft_strchr", "last", s + 4, ft_strchr(s, 'o'));
    CHECK_PTR("ft_strchr", "NUL", s + 5, ft_strchr(s, '\0'));
    CHECK_PTR("ft_strchr", "missing", NULL, ft_strchr(s, 'z'));
    CHECK_PTR("ft_strchr", "empty", NULL, ft_strchr("", 'H'));
    CHECK_PTR("ft_strchr", "unsigned char conversion", s + 1,
            ft_strchr(s, 'e' + 256));
}

void test_ft_strrchr(int *passed)
{
    const char s[] = "Hello";

    CHECK_PTR("ft_strrchr", "first", s, ft_strrchr(s, 'H'));
    CHECK_PTR("ft_strrchr", "last l", s + 3, ft_strrchr(s, 'l'));
    CHECK_PTR("ft_strrchr", "last", s + 4, ft_strrchr(s, 'o'));
    CHECK_PTR("ft_strrchr", "NUL", s + 5, ft_strrchr(s, '\0'));
    CHECK_PTR("ft_strrchr", "missing", NULL, ft_strrchr(s, 'z'));
    CHECK_PTR("ft_strrchr", "empty", NULL, ft_strrchr("", 'H'));
}

static void compare_strncmp(const char *label, const char *a,
        const char *b, size_t n, int *passed)
{
    CHECK_INT("ft_strncmp", label,
        sign_of(strncmp(a, b, n)), sign_of(ft_strncmp(a, b, n)));
}

void test_ft_strncmp(int *passed)
{
    compare_strncmp("equal", "Hello", "Hello", 5, passed);
    compare_strncmp("less", "Hello", "World", 5, passed);
    compare_strncmp("greater", "z", "a", 1, passed);
    compare_strncmp("n=0", "Hello", "World", 0, passed);
    compare_strncmp("prefix", "Hello", "Hellp", 4, passed);
    compare_strncmp("different after prefix", "Hello", "Hellp", 5, passed);
    compare_strncmp("shorter", "abc", "abcd", 10, passed);
    compare_strncmp("unsigned bytes", "\xff", "\x01", 1, passed);
    compare_strncmp("embedded NUL", "a\0b", "a\0c", 3, passed);
}

void test_ft_strnstr(int *passed)
{
    const char s[] = "Hello, World!";

    CHECK_PTR("ft_strnstr", "normal", s + 7, ft_strnstr(s, "World", 13));
    CHECK_PTR("ft_strnstr", "exact fit", s + 7, ft_strnstr(s, "World", 12));
    CHECK_PTR("ft_strnstr", "too short", NULL, ft_strnstr(s, "World", 11));
    CHECK_PTR("ft_strnstr", "not found", NULL, ft_strnstr(s, "France", 13));
    CHECK_PTR("ft_strnstr", "empty needle", s, ft_strnstr(s, "", 0));
    CHECK_PTR("ft_strnstr", "length zero", NULL, ft_strnstr(s, "H", 0));
    CHECK_PTR("ft_strnstr", "empty haystack", NULL, ft_strnstr("", "x", 4));
    CHECK_PTR("ft_strnstr", "after NUL", NULL, ft_strnstr("ab\0cd", "cd", 5));
}

void test_ft_strlcpy(int *passed)
{
    char dst[20];
    size_t n;

    memset(dst, 'X', sizeof(dst));
    n = ft_strlcpy(dst, "Hello, World!", sizeof(dst));
    CHECK_SIZE("ft_strlcpy", "full return", 13, n);
    CHECK_STR("ft_strlcpy", "full contents", "Hello, World!", dst);
    memset(dst, 'X', sizeof(dst));
    n = ft_strlcpy(dst, "Hello, World!", 6);
    CHECK_SIZE("ft_strlcpy", "short return", 13, n);
    CHECK_STR("ft_strlcpy", "short contents", "Hello", dst);
    memset(dst, 'X', sizeof(dst));
    n = ft_strlcpy(dst, "Hello", 0);
    CHECK_SIZE("ft_strlcpy", "size zero return", 5, n);
    CHECK_INT("ft_strlcpy", "size zero unchanged", 'X', dst[0]);
    memset(dst, 'X', sizeof(dst));
    n = ft_strlcpy(dst, "Hello", 1);
    CHECK_SIZE("ft_strlcpy", "size one return", 5, n);
    CHECK_INT("ft_strlcpy", "size one NUL", 0, dst[0]);
    n = ft_strlcpy(dst, "", sizeof(dst));
    CHECK_SIZE("ft_strlcpy", "empty return", 0, n);
    CHECK_STR("ft_strlcpy", "empty contents", "", dst);
}

void test_ft_strlcat(int *passed)
{
    char dst[20];
    size_t n;

    strcpy(dst, "Hello");
    n = ft_strlcat(dst, ", World!", sizeof(dst));
    CHECK_SIZE("ft_strlcat", "fits return", 13, n);
    CHECK_STR("ft_strlcat", "fits contents", "Hello, World!", dst);
    strcpy(dst, "Hello");
    n = ft_strlcat(dst, ", World!", 10);
    CHECK_SIZE("ft_strlcat", "truncated return", 13, n);
    CHECK_STR("ft_strlcat", "truncated contents", "Hello, Wo", dst);
    strcpy(dst, "Hello");
    n = ft_strlcat(dst, "World", 3);
    CHECK_SIZE("ft_strlcat", "size smaller than dst", 8, n);
    CHECK_STR("ft_strlcat", "unchanged dst", "Hello", dst);
    strcpy(dst, "Hello");
    n = ft_strlcat(dst, "World", 0);
    CHECK_SIZE("ft_strlcat", "size zero", 5, n);
    CHECK_STR("ft_strlcat", "size zero unchanged", "Hello", dst);
    dst[0] = '\0';
    n = ft_strlcat(dst, "World", sizeof(dst));
    CHECK_SIZE("ft_strlcat", "empty dst return", 5, n);
    CHECK_STR("ft_strlcat", "empty dst contents", "World", dst);
    strcpy(dst, "Hello");
    n = ft_strlcat(dst, "", sizeof(dst));
    CHECK_SIZE("ft_strlcat", "empty src return", 5, n);
    CHECK_STR("ft_strlcat", "empty src contents", "Hello", dst);
}

void test_ft_strdup(int *passed)
{
    char src[] = "Hello";
    char *dup = ft_strdup(src);

    CHECK_STR("ft_strdup", "contents", "Hello", dup);
    CHECK_TRUE("ft_strdup", "distinct allocation", dup != src && dup != NULL);
    if (dup)
    {
        src[0] = 'X';
        CHECK_STR("ft_strdup", "independent data", "Hello", dup);
    }
    free(dup);
    check_owned_string("ft_strdup", "empty", "", ft_strdup(""), passed);
}

void test_ft_substr(int *passed)
{
    check_owned_string("ft_substr", "middle", "World",
        ft_substr("Hello, World!", 7, 5), passed);
    check_owned_string("ft_substr", "beginning", "Hello",
        ft_substr("Hello, World!", 0, 5), passed);
    check_owned_string("ft_substr", "oversized len", "llo",
        ft_substr("Hello", 2, 50), passed);
    check_owned_string("ft_substr", "zero len", "",
        ft_substr("Hello", 2, 0), passed);
    check_owned_string("ft_substr", "start out of bounds", "",
        ft_substr("Hello", 20, 3), passed);
    check_owned_string("ft_substr", "empty", "",
        ft_substr("", 0, 10), passed);
}

void test_ft_strjoin(int *passed)
{
    check_owned_string("ft_strjoin", "normal", "Hello, World!",
        ft_strjoin("Hello", ", World!"), passed);
    check_owned_string("ft_strjoin", "both empty", "",
        ft_strjoin("", ""), passed);
    check_owned_string("ft_strjoin", "left empty", "World",
        ft_strjoin("", "World"), passed);
    check_owned_string("ft_strjoin", "right empty", "Hello",
        ft_strjoin("Hello", ""), passed);
}

void test_ft_strtrim(int *passed)
{
    check_owned_string("ft_strtrim", "spaces", "Hello",
        ft_strtrim("   Hello   ", " "), passed);
    check_owned_string("ft_strtrim", "multiple characters", "Hello",
        ft_strtrim("x\t Hello \tx", "x \t"), passed);
    check_owned_string("ft_strtrim", "nothing to trim", "Hello",
        ft_strtrim("Hello", "x"), passed);
    check_owned_string("ft_strtrim", "everything trimmed", "",
        ft_strtrim("xxxx", "x"), passed);
    check_owned_string("ft_strtrim", "empty input", "",
        ft_strtrim("", "x"), passed);
    check_owned_string("ft_strtrim", "empty set", " xx ",
        ft_strtrim(" xx ", ""), passed);
}

static void check_split(const char *label, char **actual,
        const char *const *expected, int *passed)
{
    size_t i = 0;
    size_t j;

    CHECK_TRUE("ft_split", label, actual != NULL);
    if (!actual)
        return;
    while (expected[i])
    {
        if (!actual[i])
        {
            CHECK_TRUE("ft_split", "missing element", 0);
            break;
        }
        CHECK_STR("ft_split", label, expected[i], actual[i]);
        i++;
    }
    if (!expected[i])
        CHECK_PTR("ft_split", "NULL terminator", NULL, actual[i]);
    /* Valid output is NULL-terminated; bound cleanup on corrupted outputs. */
    for (j = 0; j < 1000 && actual[j]; j++)
        free(actual[j]);
    if (j == 1000)
        CHECK_TRUE("ft_split", "terminator missing", 0);
    free(actual);
}

void test_ft_split(int *passed)
{
    static const char *const normal[] = {"Hello", "World", "42", NULL};
    static const char *const empty[] = {NULL};
    static const char *const single[] = {"HelloWorld", NULL};
    static const char *const repeated[] = {"a", "b", "c", NULL};

    check_split("normal", ft_split("Hello,World,42", ','), normal, passed);
    check_split("empty", ft_split("", ','), empty, passed);
    check_split("only delimiters", ft_split(",,,", ','), empty, passed);
    check_split("no delimiters", ft_split("HelloWorld", ','), single, passed);
    check_split("repeated delimiters", ft_split(",a,,b,c,", ','), repeated, passed);
    check_split("NUL separator", ft_split("HelloWorld", '\0'), single, passed);
}

static char map_char(unsigned int i, char c)
{
    return (char)(c + (int)(i % 26));
}

static void iter_char(unsigned int i, char *c)
{
    *c = map_char(i, *c);
}

void test_ft_strmapi(int *passed)
{
    check_owned_string("ft_strmapi", "normal", "ace",
        ft_strmapi("abc", map_char), passed);
    check_owned_string("ft_strmapi", "empty", "",
        ft_strmapi("", map_char), passed);
    check_owned_string("ft_strmapi", "single", "x",
        ft_strmapi("x", map_char), passed);
}

void test_ft_striteri(int *passed)
{
    char s1[] = "abc";
    char s2[] = "";
    char s3[] = "x";

    ft_striteri(s1, iter_char);
    ft_striteri(s2, iter_char);
    ft_striteri(s3, iter_char);
    CHECK_STR("ft_striteri", "normal", "ace", s1);
    CHECK_STR("ft_striteri", "empty", "", s2);
    CHECK_STR("ft_striteri", "single", "x", s3);
}
