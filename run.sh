#!/bin/bash

make re

valgrind --suppressions=valgrind.supp --leak-check=full --show-leak-kinds=all ./minishell

make fclean