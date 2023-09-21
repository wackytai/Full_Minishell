NAME = minishell
LIB = ./inc/minishell.h
LIBFT = ./libft_gnl/libft.a
LIBFT_DIR = ./libft_gnl
C_SOURCES = ./src/lst_utils.c ./src/lst_utils2.c ./src/files.c ./src/clean.c \
			./src/print.c ./src/lexer.c ./src/lexer_utils.c ./src/lexer_utils2.c \
			./src/parser.c ./src/parser_utils.c ./src/env_utils.c ./src/env_utils2.c \
			./src/cmd_utils.c ./src/executer.c ./src/executer_utils.c \
			./src/process_utils.c ./src/signals.c ./src/wildcards_utils.c \
			./src/wildcards_utils2.c ./src/wildcards_utils3.c ./src/operators.c \
			./src/builtins.c ./src/builtins2.c ./src/builtins_utils.c \
			./src/builtins_utils2.c ./src/executer_utils2.c ./src/clean2.c

CC = @cc
CFLAGS = -Wall -Werror -Wextra -g -lreadline

all:	$(NAME)
$(NAME):	$(C_SOURCES)
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
			$(CC) $(CFLAGS) $(^) -o $(@) $(LIBFT) -fsanitize=address,undefined

clean:
		@rm -f *.o
		@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean: clean
		@rm -f $(NAME)
		@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re