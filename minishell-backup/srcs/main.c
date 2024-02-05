/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:17:43 by mhuszar           #+#    #+#             */
/*   Updated: 2024/01/26 17:56:54 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialize_node(t_data *node, char **envp)
{
	node->env_len = 0;
	node->envp = envp;
	node->home = getenv("HOME");
	node->oldpwd = getenv("OLDPWD");
	node->pwd = getenv("PWD");
}

void	ft_initialize(t_data *node, char **envp)
{
	char	*input;

	while (1)
	{
		mode(node, INTERACTIVE);
		input = readline(GREEN "minishell$ " RESET);
		mode(node, NON_INTERACTIVE);
		if (!input)
		{
			printf("exit\n");
			free(input);
			exit(EXIT_FAILURE);
		}
		else if (*input)
		{
			if (ft_strchr(input, '=') == 1) //should change this cause of quotes
				node->line_for_export = ft_strdup(input);
			else if (ft_strcmp(input, "\n") == 0)
				break ;
			initialize_node(node, envp);
			add_history(input);
			entry_check(node, input);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*node;

	(void)argc;
	(void)argv;
	node = (t_data *)malloc(sizeof(t_data));
	if (node == NULL)
	{
		perror("Failed to allocate memory for node.");
		exit(EXIT_FAILURE);
	}
	ft_set(node);
	ft_initialize(node, envp);
	close(node->std_in);
	close(node->std_out);
	free(node);
	return (0);
}
