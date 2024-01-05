/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:17:43 by mhuszar           #+#    #+#             */
/*   Updated: 2024/01/05 14:34:51 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
        input2 = readline(GREEN "student@minishell$ " RESET);
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
