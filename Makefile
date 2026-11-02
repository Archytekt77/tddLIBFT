NAME        := test_libft
BONUS_NAME  := test_libft_bonus
LIBFT_DIR   ?= ../Libft
LIBFT      := $(LIBFT_DIR)/libft.a
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -std=c99
CPPFLAGS    := -I. -I$(LIBFT_DIR)
OBJ_DIR     := .obj

SRC := main.c tdd.c character_functions_tests.c string_functions_tests.c \
       number_functions_tests.c memory_functions_tests.c writing_functions_tests.c

OBJ       := $(addprefix $(OBJ_DIR)/mandatory/,$(SRC:.c=.o))
BONUS_OBJ := $(addprefix $(OBJ_DIR)/bonus/,$(SRC:.c=.o)) $(OBJ_DIR)/bonus/bonus_tests.o

.PHONY: all libft libft_bonus bonus test test_bonus run run_bonus clean fclean re

all: $(NAME)

libft:
	$(MAKE) -C $(LIBFT_DIR)

libft_bonus:
	$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME): $(OBJ) libft
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $@

$(BONUS_NAME): $(BONUS_OBJ) libft_bonus
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) -o $@

$(OBJ_DIR)/mandatory/%.o: %.c tdd.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/bonus/%.o: %.c tdd.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -DTEST_BONUS -c $< -o $@

bonus: $(BONUS_NAME)

test run: $(NAME)
	./$(NAME)

test_bonus run_bonus: $(BONUS_NAME)
	./$(BONUS_NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all
