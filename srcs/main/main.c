/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:17:43 by mhuszar           #+#    #+#             */
/*   Updated: 2024/02/27 18:06:06 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	entry_check(t_data *node, char *line)
{
	char	**arr;
	t_token	**tokens;
	int		ret_val;

	if (!ft_lexical_checker(line, 0, 0, '\0'))
		return (2);
	line = ft_upgrade_spaces(line, 0, 0, 0);
	tokens = ft_calloc(sizeof(t_token *), pipe_counter(line));
	if (!tokens)
		ft_exit(node, 1, "Memory allocation failed at entry check");
	arr = parse_input(line);
	if (!arr)
		ft_exit(node, 1, "Memory allocation failed at entry check");
	process_words(&tokens, arr, line, node);
	node->tokens = tokens;
	node->input_line = line;
	node->arr = arr;
	ft_localvars(tokens, node, pipe_counter(line));
	if (!check_for_heredoc(node, tokens, pipe_counter(line)))
		return (130);
	ret_val = executor_init(node, tokens, pipe_counter(line), line);
	ft_cleanup(node, tokens, line, arr);
	return (ret_val);
}

char	**dup_envp(char **envp)
{
	int		counter;
	char	**result;
	int		counter2;

	counter = 0;
	while (envp[counter])
		counter++;
	result = malloc(sizeof(char *) * counter);
	if (!result)
		return (NULL);
	counter2 = 0;
	while (counter2 < counter - 1)
	{
		result[counter2] = ft_strdup(envp[counter2]);
		if (!result[counter2])
			return (NULL);
		counter2++;
	}
	result[counter2] = NULL;
	return (result);
}

void	initialize_node(t_data *node, char **envp)
{
	(void)envp;
	node->env_len = 0;
	node->home = getenv("HOME");
	node->oldpwd = getenv("OLDPWD");
	node->pwd = getenv("PWD");
	node->in_child = 0;
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
			free_vars(node->local_vars);
			ft_free_array(node->envp);
			free(node);
			exit(EXIT_FAILURE);
		}
		else if (*input)
		{
			if (ft_strcmp(input, "\n") == 0)
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

	(void)argv;
	if (argc != 1)
		return (write(2, "Error: too many arguments\n", 26));
	node = (t_data *)malloc(sizeof(t_data));
	if (node == NULL)
		handle_error("Memory allocation failed for node.", 1);
	ft_set(node);
	node->envp = dup_envp(envp);
	node->last_return = 0;
	ft_initialize(node, envp);
	close(node->std_in);
	close(node->std_out);
	return (0);
}
