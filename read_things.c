/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:17:43 by mhuszar           #+#    #+#             */
/*   Updated: 2024/01/04 16:07:20 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	entry_check(char *str, char *ter)
{
	char **input;

	input = ft_split(ter, ' ', 0, 0);
	if (!input)
		write(2, "Error\n", 6);
	if (ft_strcmp(input[0], "pwd") == 0)
		printf("%s\n", str);
	else if (ft_strcmp(input[0], "exit") == 0)
		exit(0);
	else
		printf("shell: command not found: %s\n", ter);
}

int main(void)
{
	t_data *node;
    char *input;
	char *input2;
    size_t size = 1024;

	node = (t_data *)malloc(sizeof(t_data));
    input = (char *)malloc(size);
    if (input == NULL)
	{
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    if (getcwd(input, size) == NULL) 
	{
        perror("getcwd() error");
        exit(EXIT_FAILURE);
    }
	// input = ft_strjoin(input, "$ ", 1);
	// input = ft_strjoin("student@c0r0p0:~", input, 0);
    while (1)
	{
        input2 = readline("student@c0r0p0$ ");
        if (!input2)
            break;
        else if (*input2)
        {
			node->path = input;
			add_history(input2);
			entry_check( input, input2);
		}
    }
	free(input); 
    free(input2);
    write(1, "exiting minishell\n", 17);
    return 0;
}
