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

void	ft_cleanup(t_token **tokens, char *line, char **arr)
{
	free_tokens(tokens);
	free(line);
	free_arr(arr);
}

int	entry_check(t_data *node, char *line)
{
	char	**arr;
	t_token	**tokens;
	int		ret_val;

	if (!ft_lexical_checker(line))
		return (2);
	line = ft_upgrade_spaces(line);
	tokens = ft_calloc(sizeof(t_token *), pipe_counter(line));
	if (!tokens)
	{
		perror("Memory allocation failed");
		return (127);
	}
	arr = parse_input(line);
	if (!arr)
	{
		free(tokens);
		return (127);
	}
	process_words(&tokens, arr, line, node);
	check_for_heredoc(tokens, pipe_counter(line));
	ret_val = executor_init(node, tokens, pipe_counter(line), line);
	ft_cleanup(tokens, line, arr);
	return (ret_val);
}

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
			node->last_return = entry_check(node, input);
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
