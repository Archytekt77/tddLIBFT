# Libft TDD - corrected tests

This is a stand-alone test program. It does **not** modify your Libft.

Expected directory layout (default):

```
work/
├── Libft/
│   ├── Makefile
│   ├── libft.h
│   └── ft_*.c
└── Libft_TDD_corrige/
    ├── Makefile
    ├── main.c
    ├── tdd.h
    └── *_tests.c
```

Commands:

```sh
make                # build mandatory tests (compiles libft.a first)
make test           # build + execute mandatory tests
make bonus          # build tests for mandatory + bonus functions
make test_bonus     # build + execute mandatory + bonus tests
make fclean
```

If your library folder is named `libft` or located elsewhere:

```sh
make test LIBFT_DIR=../libft
make test_bonus LIBFT_DIR=/absolute/path/to/libft
```

The standard 42 Libft contains 34 mandatory functions and 9 bonus functions.
The bonus build assumes your Libft implements a `bonus` Makefile target.
Tests compare equivalent libc behavior for applicable functions; others have
explicit expected outputs. `ft_strncmp` and `ft_memcmp` are checked by sign,
not by a particular positive/negative magnitude.

Note: A PASS does not prove absence of memory leaks or undefined behavior.
If installed, run `valgrind --leak-check=full --track-origins=yes ./test_libft`
and `valgrind --leak-check=full --track-origins=yes ./test_libft_bonus`.
Test binaries, build artifacts, and the third-party `LibftTester` were omitted
from this repaired package.
