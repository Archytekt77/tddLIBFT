NAME       := test_libft
# Dossier de ta Libft : a modifier ici si elle est ailleurs.
LIBFT_DIR  ?= ../Libft
LIBFT      := $(LIBFT_DIR)/libft.a
CC         := cc
CFLAGS     := -Wall -Wextra -Werror
CPPFLAGS   := -I. -I$(LIBFT_DIR)
OBJ_DIR    := .obj

SRC := main.c tdd.c character_functions_tests.c string_functions_tests.c \
       number_functions_tests.c memory_functions_tests.c \
       writing_functions_tests.c list_functions_tests.c
OBJ := $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

.DEFAULT_GOAL := all
.PHONY: all run clean fclean re

all:
	@$(MAKE) --no-print-directory -C "$(LIBFT_DIR)"
	@$(MAKE) --no-print-directory $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $@

$(LIBFT):
	@$(MAKE) --no-print-directory -C "$(LIBFT_DIR)"

$(OBJ_DIR)/%.o: %.c tdd.h $(LIBFT_DIR)/libft.h Makefile
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

run: all
	@./$(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re:
	@$(MAKE) --no-print-directory fclean
	@$(MAKE) --no-print-directory all
