#!/bin/bash

RED="\033[0;31m"
BLUE="\033[0;34m"
GREEN="\033[0;32m"
RESET="\033[0m"

echo -e "${BLUE}Testing minishell...${RESET}"

# Test the 'echo' command
echo "echo Hello, World!" | ./minishell > output.txt
if grep -q "Hello, World!" output.txt; then
    echo -e "${GREEN}echo command passed${RESET}"
else
    echo -e "${RED}echo command failed${RESET}"
fi

# Test the 'cd' command

# Test the 'pwd' command

# Test the 'export' command

# Test the 'unset' command

# Test the 'env' command

# Test the 'exit' command

# Test others...


rm output.txt