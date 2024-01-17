/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumon <sumon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:17:43 by mhuszar           #+#    #+#             */
/*   Updated: 2024/01/17 09:33:54 by sumon            ###   ########.fr       */
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
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
		input2 = readline(GREEN "student@minishell$ " RESET);
		if (!input2)
		{
			printf("\n");
			printf("exit\n");
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
