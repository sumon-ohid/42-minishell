NAME = minishell
CC = cc
CC1 = clang
CC2 = gcc
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address
HEADER = minishell.h

#Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

SRC = 	srcs/main/main.c \
		srcs/libft/ft_split.c \
		srcs/executions/cmd.c \
		srcs/executions/cmd01.c \
		srcs/executions/cmd02.c \
		srcs/libft/libft_helpers.c \
		srcs/libft/libft_helpers1.c \
		srcs/libft/libft_helpers2.c \
		srcs/libft/libft_helpers3.c \
		srcs/parsing/tokenize.c\
		srcs/parsing/tokenize1.c\
		srcs/builtins/ft_cd.c \
		srcs/builtins/ft_echo.c \
		srcs/builtins/ft_echo_extra.c \
		srcs/builtins/ft_env.c \
		srcs/builtins/ft_export.c \
		srcs/builtins/ft_pwd.c \
		srcs/builtins/ft_unset.c \
		srcs/builtins/ft_exit.c \
		srcs/main/ft_free.c \
		srcs/main/handle_error.c \
		srcs/heredoc/heredoc.c \
		srcs/heredoc/heredoc_extra.c \
		srcs/executions/pipex.c \
		srcs/signals/signals.c \
		srcs/executions/redirects.c \
		srcs/executions/redirects_extra.c \
		srcs/parsing/lexer.c \
		srcs/parsing/lexer_extra.c \
		srcs/signals/ft_lastvalue.c \
		srcs/libft/ft_itoa.c \
		srcs/parsing/ft_split_special_edition.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

clean:
	rm -f $(OBJ) $(BN_OBJ)

fclean: clean
	rm -f $(NAME)

smooth: all clean

re:
	@$(MAKE) fclean
	@$(MAKE) all

celan:
	@echo "$(YELLOW)Lol, that's not quite what you wanted to write, huh?$(DEF_COLOR)"
	
fcelan: celan

clear: celan

strict:
	@echo "$(GREEN)Compiling with $(YELLOW)$(CC1)$(GREEN)...$(DEF_COLOR)"
	@$(MAKE) all CC=$(CC1)
	@echo "$(GREEN)Cleaning up...$(DEF_COLOR)"
	@$(MAKE) fclean
	@echo "$(GREEN)Compiling with $(YELLOW)$(CC2)$(GREEN)...$(DEF_COLOR)"
	@$(MAKE) all CC=$(CC2)
	@echo "$(GREEN)Cleaning up again...$(DEF_COLOR)"
	@$(MAKE) clean
	@echo "$(GREEN)Tested for both compilers.$(DEF_COLOR)"

.PHONY: all clean fclean re bonus strict smooth celan fcelan clear
