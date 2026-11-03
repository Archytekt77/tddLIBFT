#include "tdd.h"
#include <errno.h>

#ifdef _WIN32
# include <io.h>
# include <fcntl.h>
# define pipe(fd) _pipe((fd), 4096, _O_BINARY)
#endif

/* A pipe verifies both the exact output and the supplied file descriptor. */
static void check_fd_output(const char *fn, const char *label,
        const char *expected, void (*write_fn)(int), int *passed)
{
    int fd[2];
    char buf[256];
    size_t total;
    ssize_t n;

    if (pipe(fd) != 0)
    {
        CHECK_TRUE(fn, "pipe creation", 0);
        return;
    }
    write_fn(fd[1]);
    close(fd[1]);
    total = 0;
    while (total < sizeof(buf) - 1)
    {
        n = read(fd[0], buf + total, sizeof(buf) - 1 - total);
        if (n == 0)
            break;
        if (n < 0)
        {
            if (errno == EINTR)
                continue;
            CHECK_TRUE(fn, "reading pipe", 0);
            break;
        }
        total += (size_t)n;
    }
    close(fd[0]);
    buf[total] = '\0';
    CHECK_STR(fn, label, expected, buf);
    CHECK_SIZE(fn, "output length", strlen(expected), total);
}

static void put_char_a(int fd) { ft_putchar_fd('A', fd); }
static void put_char_nul(int fd) { ft_putchar_fd('\0', fd); }
static void put_str_hello(int fd) { ft_putstr_fd("Hello", fd); }
static void put_str_empty(int fd) { ft_putstr_fd("", fd); }
static void put_line_hello(int fd) { ft_putendl_fd("Hello", fd); }
static void put_line_empty(int fd) { ft_putendl_fd("", fd); }
static void put_num_zero(int fd) { ft_putnbr_fd(0, fd); }
static void put_num_pos(int fd) { ft_putnbr_fd(42, fd); }
static void put_num_neg(int fd) { ft_putnbr_fd(-42, fd); }
static void put_num_min(int fd) { ft_putnbr_fd(INT_MIN, fd); }
static void put_num_max(int fd) { ft_putnbr_fd(INT_MAX, fd); }

void test_ft_putchar_fd(int *passed)
{
    int fd[2];
    unsigned char c = 0xff;
    ssize_t n;

    check_fd_output("ft_putchar_fd", "A", "A", put_char_a, passed);
    if (pipe(fd) != 0)
    {
        CHECK_TRUE("ft_putchar_fd", "pipe creation for NUL", 0);
        return;
    }
    put_char_nul(fd[1]);
    close(fd[1]);
    n = read(fd[0], &c, 1);
    close(fd[0]);
    CHECK_INT("ft_putchar_fd", "NUL byte count", 1, n);
    CHECK_INT("ft_putchar_fd", "NUL byte content", 0, c);
}

void test_ft_putstr_fd(int *passed)
{
    check_fd_output("ft_putstr_fd", "normal", "Hello", put_str_hello, passed);
    check_fd_output("ft_putstr_fd", "empty", "", put_str_empty, passed);
}

void test_ft_putendl_fd(int *passed)
{
    check_fd_output("ft_putendl_fd", "normal", "Hello\n", put_line_hello, passed);
    check_fd_output("ft_putendl_fd", "empty", "\n", put_line_empty, passed);
}

void test_ft_putnbr_fd(int *passed)
{
    check_fd_output("ft_putnbr_fd", "zero", "0", put_num_zero, passed);
    check_fd_output("ft_putnbr_fd", "positive", "42", put_num_pos, passed);
    check_fd_output("ft_putnbr_fd", "negative", "-42", put_num_neg, passed);
    check_fd_output("ft_putnbr_fd", "INT_MIN", "-2147483648", put_num_min, passed);
    check_fd_output("ft_putnbr_fd", "INT_MAX", "2147483647", put_num_max, passed);
}
