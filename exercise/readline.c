#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *input;

    while (1)
    {
        input = readline("minishell ➤ ");
        printf("%s\n", input);
        add_history(input);
        if (strcmp(input, "clear") == 0)
            clear_history();
        free (input);
    }
    return (0);
}