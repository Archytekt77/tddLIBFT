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
/* Redeclarations deliberately reject prototypes differing from subject v19.3. */
int ft_isalpha(int c);
int ft_isdigit(int c);
int ft_isalnum(int c);
int ft_isascii(int c);
int ft_isprint(int c);
int ft_toupper(int c);
int ft_tolower(int c);
size_t ft_strlen(const char *s);
void *ft_memset(void *s, int c, size_t n);
void ft_bzero(void *s, size_t n);
void *ft_memcpy(void *dst, const void *src, size_t n);
void *ft_memmove(void *dst, const void *src, size_t n);
size_t ft_strlcpy(char *dst, const char *src, size_t size);
size_t ft_strlcat(char *dst, const char *src, size_t size);
char *ft_strchr(const char *s, int c);
char *ft_strrchr(const char *s, int c);
int ft_strncmp(const char *s1, const char *s2, size_t n);
void *ft_memchr(const void *s, int c, size_t n);
int ft_memcmp(const void *s1, const void *s2, size_t n);
char *ft_strnstr(const char *big, const char *little, size_t len);
int ft_atoi(const char *s);
void *ft_calloc(size_t nmemb, size_t size);
char *ft_strdup(const char *s);
char *ft_substr(const char *s, unsigned int start, size_t len);
char *ft_strjoin(const char *s1, const char *s2);
char *ft_strtrim(const char *s1, const char *set);
char **ft_split(const char *s, char c);
char *ft_itoa(int n);
char *ft_strmapi(const char *s, char (*f)(unsigned int, char));
void ft_striteri(char *s, void (*f)(unsigned int, char *));
void ft_putchar_fd(char c, int fd);
void ft_putstr_fd(char *s, int fd);
void ft_putendl_fd(char *s, int fd);
void ft_putnbr_fd(int n, int fd);
t_list *ft_lstnew(void *content);
void ft_lstadd_front(t_list **lst, t_list *new_node);
unsigned int ft_lstsize(t_list *lst);
t_list *ft_lstlast(t_list *lst);
void ft_lstadd_back(t_list **lst, t_list *new_node);
void ft_lstdelone(t_list *lst, void (*del)(void *));
void ft_lstclear(t_list **lst, void (*del)(void *));
void ft_lstiter(t_list *lst, void (*f)(void *));
t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

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
