/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:41:52 by mhuszar           #+#    #+#             */
/*   Updated: 2024/02/28 10:31:09 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
typedef struct s_data
{
	char			*line_for_export;
	int				**fd;
	int				*pid;
	char				**envp; //no free
	char				*oldpwd; //no free EXCEPT IF WE EVER USE CD
						- should change this in CD
	char				*pwd; //no free EXCEPT IF WE EVER USE CD
						- should change this in CD
	char				*home; //no_free
	char			*line_temp;
	struct s_data	*next;
}						t_data;*/

void	ft_free_array(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return ;
}

void	ft_free_fds(t_data *node)
{
	int	i;
	int	**arr;

	i = 0;
	close_all(&node->fd, node->processes - 1);
	arr = node->fd;
	if (!arr)
		return ;
	while (i < node->processes - 1)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return ;
}

void	free_vars(t_vars *local_vars)
{
	t_vars	*cur;
	t_vars	*prev;

	cur = local_vars;
	while (cur)
	{
		prev = cur;
		cur = cur->next;
		free(prev->str);
		free(prev->first_half);
		free(prev->second_half);
		free(prev);
	}
}

void	free_node(t_data *node)
{
	free_tokens(node->tokens, node->processes);
	free_vars(node->local_vars);
	if (node->std_in != -1)
		close(node->std_in);
	if (node->std_out != -1)
		close(node->std_out);
	free(node->input_line);
	ft_free_array(node->arr);
	ft_free_array(node->envp);
	free(node);
}

void	ft_early_exit(t_data *node, int exit_val, char *msg)
{
	free(node->input_line);
	ft_free_array(node->envp);
	ft_free_array(node->arr);
	free_vars(node->local_vars);
	if (node->std_in != -1)
		close(node->std_in);
	if (node->std_out != -1)
		close(node->std_out);
	free(node);
	if (msg)
		handle_error(msg, exit_val);
	else
		exit(exit_val);
}

void	ft_exit(t_data *node, int exit_val, char *msg)
{
	free_node(node);
	if (msg)
		handle_error(msg, exit_val);
	else
		exit(exit_val);
}
