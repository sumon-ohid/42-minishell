#!/bin/bash

# List of commands to test
commands=("ls" "pwd" "echo hello"
          "cd" "invalid_command"
          "export TEST_VAR=hello"
          "echo \$TEST_VAR"
          "unset TEST_VAR"
          "echo \$TEST_VAR"
          "env"
          "unset PATH"
          "ls"
          "unset HOME"
          "cd"
          "cd invalid_path"
          "non_existent_command")

# Start of the temporary file content
tmp_file_content=""

for cmd in "${commands[@]}"; do
    echo "Testing command: $cmd"

    # Add the command to the temporary file content
    tmp_file_content+="$cmd\n"
done

# Write the temporary file content to a temporary file
echo -e "$tmp_file_content" >tmp.sh

# Run the commands in minishell and compare exit codes
while IFS= read -r cmd; do
    # Run the command in minishell and get the exit code
    ./minishell -c "$cmd"
    minishell_exit_code= echo $?

    # Run the command in bash and get the exit code
    bash -c "$cmd"
    bash_exit_code=echo $?

    # Compare the exit codes
    if [ "$minishell_exit_code" == "$bash_exit_code" ]; then
        echo -e "\e[32mOK\e[0m"  # Green
    else
        echo -e "\e[31mKO\e[0m"  # Red
        echo "Command: $cmd"
        echo "Minishell exit code: $minishell_exit_code"
        echo "Bash exit code: $bash_exit_code"
    fi

    # Echo the exit code of the command in minishell
    echo "Exit code of $cmd in minishell: $?"
done < tmp.sh

# Delete the temporary file
rm tmp.sh
