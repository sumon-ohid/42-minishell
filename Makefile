NAME = minishell
CC = cc
CC1 = clang
CC2 = gcc
CFLAGS = -Wall -Werror -Wextra -g
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

SRC = 	srcs/main.c \
		srcs/ft_split.c \
		srcs/cmd.c \
		srcs/libft_helpers.c \
		srcs/libft_helpers1.c \
		srcs/libft_helpers2.c \
		srcs/tokenize.c\
		srcs/tokenize1.c\
		srcs/ft_cd.c \
		srcs/ft_echo.c \
		srcs/ft_env.c \
		srcs/ft_export.c \
		srcs/ft_pwd.c \
		srcs/ft_unset.c \
		srcs/ft_free.c \
		srcs/heredoc.c \
		srcs/pipex.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -g -o $(NAME) -lreadline
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
