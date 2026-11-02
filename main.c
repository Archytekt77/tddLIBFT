#include "tdd.h"

int main(void)
{
    puts("\n=== LIBFT TESTS ===");
    puts("\nCharacter functions:");
    run_test(test_ft_isalpha, "ft_isalpha");
    run_test(test_ft_isdigit, "ft_isdigit");
    run_test(test_ft_isalnum, "ft_isalnum");
    run_test(test_ft_isascii, "ft_isascii");
    run_test(test_ft_isprint, "ft_isprint");
    run_test(test_ft_toupper, "ft_toupper");
    run_test(test_ft_tolower, "ft_tolower");

    puts("\nString functions:");
    run_test(test_ft_strlen, "ft_strlen");
    run_test(test_ft_strchr, "ft_strchr");
    run_test(test_ft_strrchr, "ft_strrchr");
    run_test(test_ft_strncmp, "ft_strncmp");
    run_test(test_ft_strnstr, "ft_strnstr");
    run_test(test_ft_strlcpy, "ft_strlcpy");
    run_test(test_ft_strlcat, "ft_strlcat");
    run_test(test_ft_strdup, "ft_strdup");
    run_test(test_ft_substr, "ft_substr");
    run_test(test_ft_strjoin, "ft_strjoin");
    run_test(test_ft_strtrim, "ft_strtrim");
    run_test(test_ft_split, "ft_split");
    run_test(test_ft_strmapi, "ft_strmapi");
    run_test(test_ft_striteri, "ft_striteri");

    puts("\nNumber functions:");
    run_test(test_ft_atoi, "ft_atoi");
    run_test(test_ft_itoa, "ft_itoa");

    puts("\nMemory functions:");
    run_test(test_ft_memset, "ft_memset");
    run_test(test_ft_bzero, "ft_bzero");
    run_test(test_ft_memcpy, "ft_memcpy");
    run_test(test_ft_memmove, "ft_memmove");
    run_test(test_ft_memchr, "ft_memchr");
    run_test(test_ft_memcmp, "ft_memcmp");
    run_test(test_ft_calloc, "ft_calloc");

    puts("\nFile descriptor functions:");
    run_test(test_ft_putchar_fd, "ft_putchar_fd");
    run_test(test_ft_putstr_fd, "ft_putstr_fd");
    run_test(test_ft_putendl_fd, "ft_putendl_fd");
    run_test(test_ft_putnbr_fd, "ft_putnbr_fd");

#ifdef TEST_BONUS
    puts("\nBonus: linked lists:");
    run_test(test_ft_lstnew, "ft_lstnew");
    run_test(test_ft_lstadd_front, "ft_lstadd_front");
    run_test(test_ft_lstadd_back, "ft_lstadd_back");
    run_test(test_ft_lstsize, "ft_lstsize");
    run_test(test_ft_lstlast, "ft_lstlast");
    run_test(test_ft_lstdelone, "ft_lstdelone");
    run_test(test_ft_lstclear, "ft_lstclear");
    run_test(test_ft_lstiter, "ft_lstiter");
    run_test(test_ft_lstmap, "ft_lstmap");
#endif
    return test_summary();
}
