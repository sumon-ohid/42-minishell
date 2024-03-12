/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:03:57 by msumon            #+#    #+#             */
/*   Updated: 2024/03/12 10:38:44 by mhuszar          ###   ########.fr       */
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

void	free_node(t_data *node)
{
	free(node->oldpwd);
	free_tokens(node->tokens, node->processes);
	if (node->std_in != -1)
		close(node->std_in);
	if (node->std_out != -1)
		close(node->std_out);
	free(node->input_line);
	if (node->status)
		free(node->status);
	node->status = NULL;
	if (node->pid)
		free(node->pid);
	node->pid = NULL;
	ft_free_array(node->envp);
	free(node);
}

void	eof_free(t_data *node)
{
	printf("exit\n");
	free(node->oldpwd);
	ft_free_array(node->envp);
	if (node->std_in != -1)
		close(node->std_in);
	if (node->std_out != -1)
		close(node->std_out);
	free(node);
	exit(EXIT_FAILURE);
}
