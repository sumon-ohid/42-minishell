#!/bin/bash

norminette -RCheckForbiddenHeader

make smooth

valgrind --suppressions=valgrind.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell

make fclean