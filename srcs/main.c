/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:17:43 by mhuszar           #+#    #+#             */
/*   Updated: 2024/01/17 16:34:49 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

void	handle_sigint(int sig)
{
	(void)sig;
	exit(0);
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

void	ft_initialize(t_data *node, char *input, char *input2)
{
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
		input2 = readline(GREEN "student@minishell$ " RESET);
		if (!input2)
		{
			printf("\n");
			printf("exit\n");
			free(input);
			free(input2);
			exit(0);
		}
		else if (*input2)
		{
			node->path = input;
			add_history(input2);
			entry_check(input, input2);
		}
	}
	free(input);
	free(input2);
}

int	main(void)
{
	t_data	*node;
	char	*input;
	char	*input2;

	input2 = NULL;
	node = (t_data *)malloc(sizeof(t_data));
	if (node == NULL)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	input = (char *)malloc(1024);
	if (input == NULL)
	{
		perror("Failed to allocate memory");
		free(node);
		exit(EXIT_FAILURE);
	}
	ft_initialize(node, input, input2);
	return (0);
}
