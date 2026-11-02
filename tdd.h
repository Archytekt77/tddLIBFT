#ifndef TDD_H
# define TDD_H

# include "libft.h"
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <stdint.h>
# include <unistd.h>

/* An assertion marks its function as failed but allows other checks to run. */
void check_int(const char *fn, const char *case_name,
        long long expected, long long actual, int *passed);
void check_size(const char *fn, const char *case_name,
        size_t expected, size_t actual, int *passed);
void check_str(const char *fn, const char *case_name,
        const char *expected, const char *actual, int *passed);
void check_ptr(const char *fn, const char *case_name,
        const void *expected, const void *actual, int *passed);
void check_mem(const char *fn, const char *case_name,
        const void *expected, const void *actual, size_t size, int *passed);
void check_true(const char *fn, const char *case_name,
        int condition, int *passed);
int  sign_of(int value);
void run_test(void (*test_func)(int *), const char *name);
int  test_summary(void);

# define CHECK_INT(fn, label, expected, actual) \
    check_int((fn), (label), (long long)(expected), (long long)(actual), passed)
# define CHECK_SIZE(fn, label, expected, actual) \
    check_size((fn), (label), (size_t)(expected), (size_t)(actual), passed)
# define CHECK_STR(fn, label, expected, actual) \
    check_str((fn), (label), (expected), (actual), passed)
# define CHECK_PTR(fn, label, expected, actual) \
    check_ptr((fn), (label), (expected), (actual), passed)
# define CHECK_MEM(fn, label, expected, actual, len) \
    check_mem((fn), (label), (expected), (actual), (len), passed)
# define CHECK_TRUE(fn, label, condition) \
    check_true((fn), (label), (condition), passed)

void test_ft_isalpha(int *passed);
void test_ft_isdigit(int *passed);
void test_ft_isalnum(int *passed);
void test_ft_isascii(int *passed);
void test_ft_isprint(int *passed);
void test_ft_toupper(int *passed);
void test_ft_tolower(int *passed);

void test_ft_strlen(int *passed);
void test_ft_strchr(int *passed);
void test_ft_strrchr(int *passed);
void test_ft_strncmp(int *passed);
void test_ft_strnstr(int *passed);
void test_ft_strlcpy(int *passed);
void test_ft_strlcat(int *passed);
void test_ft_strdup(int *passed);
void test_ft_substr(int *passed);
void test_ft_strjoin(int *passed);
void test_ft_strtrim(int *passed);
void test_ft_split(int *passed);
void test_ft_strmapi(int *passed);
void test_ft_striteri(int *passed);

void test_ft_atoi(int *passed);
void test_ft_itoa(int *passed);
void test_ft_memset(int *passed);
void test_ft_bzero(int *passed);
void test_ft_memcpy(int *passed);
void test_ft_memmove(int *passed);
void test_ft_memchr(int *passed);
void test_ft_memcmp(int *passed);
void test_ft_calloc(int *passed);
void test_ft_putchar_fd(int *passed);
void test_ft_putstr_fd(int *passed);
void test_ft_putendl_fd(int *passed);
void test_ft_putnbr_fd(int *passed);

#ifdef TEST_BONUS
void test_ft_lstnew(int *passed);
void test_ft_lstadd_front(int *passed);
void test_ft_lstadd_back(int *passed);
void test_ft_lstsize(int *passed);
void test_ft_lstlast(int *passed);
void test_ft_lstdelone(int *passed);
void test_ft_lstclear(int *passed);
void test_ft_lstiter(int *passed);
void test_ft_lstmap(int *passed);
#endif

#endif
