/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:17:43 by mhuszar           #+#    #+#             */
/*   Updated: 2024/01/15 13:18:23 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	handle_sigquit(int sig)
{
	(void)sig;
	exit(0);
}

int	main(void)
{
	t_data	*node;
	char	*input;
	char	*input2;

	node = (t_data *)malloc(sizeof(t_data));
	input = (char *)malloc(1024);
	if (input == NULL)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	while (1)
	{
		input2 = readline(GREEN "student@minishell$ " RESET);
		if (!input2)
		{
			printf("\n");
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
	return (0);
}
