/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:17:43 by mhuszar           #+#    #+#             */
/*   Updated: 2024/03/07 15:35:54 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void init_tokens(t_data *node)
{
	t_token **tokens;
	int		i;

	i = 0;
	tokens = ft_calloc(sizeof(t_token *), node->processes);
	if (!tokens)
		ft_exit(node, 1, "Memory allocation failed at entry check"); //this should be changed
	while (i < node->processes)
		tokens[i++] = NULL;
	node->tokens = tokens;
	mole_parser(&tokens, /*arr,*/ node->input_line, node);
	node->tokens = tokens;
}

int	entry_check(t_data *node, char *line)
{
	int		ret_val;

	if (!ft_lexical_checker(line, 0, 0, '\0'))
		return (-2);
	//line = ft_upgrade_spaces(line, 0, 0, 0);
	node->input_line = line;
	node->processes = pipe_counter(line);
	printf("we have %d processes\n", node->processes);
	init_tokens(node);
	/*arr = parse_input(line);
	if (!arr)
		ft_exit(node, 1, "Memory allocation failed at entry check");*/
	//node->arr = arr;
	if (!check_for_heredoc(node, node->tokens, pipe_counter(line)))
		return (2);
	ret_val = executor_init(node, node->tokens, pipe_counter(line), line);
	ft_cleanup(node, node->tokens, line);
	if (node->last_return == -99)
		return (-1);
	else
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
	node->status = NULL;
	node->pid = NULL;
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
			eof_free(node);
		}
		else if (*input)
		{
			if (g_signal == CTRL_C)
			{
				node->last_return = 2;
				g_signal = 0;
			}
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
