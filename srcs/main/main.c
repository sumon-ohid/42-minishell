/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:17:43 by mhuszar           #+#    #+#             */
/*   Updated: 2024/03/14 19:34:19 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_tokens(t_data *node)
{
	t_token	**tokens;
	int		i;

	i = 0;
	node->processes = pipe_counter(node->input_line);
	tokens = ft_calloc(sizeof(t_token *), node->processes + 1);
	if (!tokens)
		parse_error(node, 0, "malloc at init tokens failed", -1);
	while (i <= node->processes)
		tokens[i++] = NULL;
	node->tokens = tokens;
	mole_parser(&(node->tokens), node->input_line, node);
}

int	entry_check(t_data *node, char *line)
{
	int	ret_val;

	node->input_line = line;
	if (!ft_lexical_checker(node, 0, 0, '\0'))
		return (-2);
	init_tokens(node);
	if (!check_for_heredoc(node, node->tokens, pipe_counter(line)))
		return (2);
	ret_val = executor_init(node, node->tokens, pipe_counter(line), line);
	ft_cleanup(node, node->tokens, line);
	if (node->last_return == -99)
		return (-1);
	else
		return (ret_val);
}

void	initialize_node(t_data *node)
{
	node->home = getenv("HOME");
	node->in_child = 0;
	node->status = NULL;
	node->pid = NULL;
	node->command_flag = 0;
	node->msg = 0;
	node->delim_turn = false;
	node->exported = false;
}

void	ft_initialize(t_data *node)
{
	char	*input;

	while (1)
	{
		mode(node, INTERACTIVE);
		input = readline(GREEN "minishell$ " RESET);
		mode(node, NON_INTERACTIVE);
		if (g_signal == CTRL_C)
		{
			node->last_return = 2;
			g_signal = 0;
		}
		if (!input)
		{
			eof_free(node);
		}
		else if (*input)
		{
			if (ft_strcmp(input, "\n") == 0)
				break ;
			initialize_node(node);
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
	node->envp = dup_envp(envp, node);
	if (!node->envp)
		parse_error(node, 0, "dup_envp failed", -1);
	add_missing_envs(node);
	adjust_shlevel(node->envp, node);
	node->last_return = 0;
	ft_initialize(node);
	close(node->std_in);
	close(node->std_out);
	return (0);
}
