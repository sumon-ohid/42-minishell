# MiniShell
## As beautiful as a shell

MiniShell is a minimalistic shell program designed to replicate the basic functionalities of the Bash shell. It provides a command-line interface for users to interact with the operating system by executing commands and managing processes.

## Features

- **Command Execution**: Execute commands entered by the user.
- **Built-in Commands**: Supports built-in commands such as `cd`, `pwd`, `echo`, `export`, `unset`, `exit` etc.
- **Input/Output Redirection**: Supports input/output redirection using `<` and `>` operators.
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

4. Run MiniShell:

    ```
    ./minishell
    ```

## Usage

Once MiniShell is running, you can use it just like any other shell. Enter commands at the prompt and press `Enter` to execute them. MiniShell supports a variety of features common to Unix-like shells, including input/output redirection, pipeline commands, and background processes.

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

MiniShell was created by [Sumon](https://github.com/sumon-ohid) and [Leske](https://github.com/leske42) . It was inspired by the Bash shell and is intended to provide a lightweight alternative with essential functionalities.

## License

This project is licensed under the [MIT License](LICENSE). Feel free to modify and distribute it according to your needs. !!!! Please don't use it directly for 42 School projects !!!!
