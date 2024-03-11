/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:03:57 by msumon            #+#    #+#             */
/*   Updated: 2024/03/10 14:43:46 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cleanup(t_data *node, t_token **tokens, char *line)
{
	free_tokens(tokens, node->processes);
	free(line);
}

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
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
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

void	eof_free(t_data *node)
{
	printf("exit\n");
	//free_vars(node->local_vars);
	ft_free_array(node->envp);
	if (node->std_in != -1)
		close(node->std_in);
	if (node->std_out != -1)
		close(node->std_out);
	free(node);
	exit(EXIT_FAILURE);
}
