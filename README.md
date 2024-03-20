# Minishell
## As beautiful as a shell
Minishell is one of the largest project in 42 School. It took us almost 2 months to evaluate the project. But we learnt so much through out this time. Also this is our first team project. Through this project we learnt how computer executes a command, proccesses, builtins (echo , export etc.) and so on. We learnt how to contribute and split problems with others on the same project and come up with a solution. Overall it's a full-stack , real-world, useful, stressful and fun project.

## Features

- **Command Execution**: Execute commands entered by the user.
- **Built-in Commands**: Supports built-in commands such as `cd`, `pwd`, `echo`, `export`, `unset`, `exit` etc.
- **Input/Output Redirection**: Supports input/output redirection using `<` and `>` operators.
- **Heredoc/Append Mode**: Supports heredoc and append using `<<` and `>>` operators.
- **Pipeline Commands**: Supports chaining multiple commands together using the `|` operator.
- **Signal Handling**: Handles signals such as `Ctrl+C` for interrupt and `Ctrl+D` for exit.

## Installation

1. Clone the repository:

    ```
    https://github.com/sumon-ohid/42-minishell.git
    ```

2. Navigate to the project directory:

    ```
    cd minishell
    ```

3. Compile the source code:

    ```
    make
    ```

4. Run Minishell:

    ```
    ./minishell
    ```

## Usage
Here are some examples of commands you can run:

- **Executing a command**:

    ```
    ls -l
    ```

- **Changing directory**:

    ```
    cd /path/to/directory
    ```

- **Redirecting input/output**:

    ```
    cat input.txt > output.txt
    ```

- **Chaining commands**:

    ```
    ls -l | grep "file"
    ```

## Credits

Created by [Sumon](https://github.com/sumon-ohid) and [Leske](https://github.com/leske42) . 

## Note

Feel free to modify and distribute it according to your needs. !!!! Please don't use it directly for 42 School projects !!!!
