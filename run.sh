#!/bin/bash

#norminette -RCheckForbiddenHeader

make smooth

valgrind --suppressions=valgrind.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children=yes ./minishell

make fclean