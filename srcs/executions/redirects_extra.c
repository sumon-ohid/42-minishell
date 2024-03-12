/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:02:36 by msumon            #+#    #+#             */
/*   Updated: 2024/03/12 11:57:41 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	str_is_nothing(char *str)
{
	int	c;

	c = 0;
	if (!str)
		return (1);
	if (ft_strcmp(str, "") == 0)
		return (1);
	else
		return (0);
}

int	redirect_in(char *input, int mode, t_data *node)
{
	int	fd1;

	fd1 = open(input, O_RDONLY);
	if (fd1 == -1)
	{
		printf("minishell: %s: No such file or directory\n", input);
		if (mode == 1)
		{
			ft_free_fds(node);
			ft_exit(node, 1, NULL);
		}
		else
			return (node->last_return = -99, 0);
	}
	if (dup2(fd1, STDIN_FILENO) == -1)
	{
		ft_free_fds(node);
		ft_exit(node, errno, "dup2 failed");
	}
	close(fd1);
	return (1);
}

int	redirect_out(char *output, int mode, t_data *node)
{
	int	fd2;

	if (str_is_nothing(output))
		return (printf("minishell: : No such file or directory\n"),
			node->last_return = -99, 0);
	fd2 = open(output, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (fd2 == -1)
	{
		printf("minishell: %s: Permission denied\n", output);
		if (mode == 1)
		{
			ft_free_fds(node);
			ft_exit(node, 1, NULL);
		}
		else
			return (node->last_return = -99, 0);
	}
	if (dup2(fd2, STDOUT_FILENO) == -1)
	{
		ft_free_fds(node);
		ft_exit(node, errno, "dup2 failed");
	}
	close(fd2);
	return (1);
}

int	redirect_out_append(char *output, int mode, t_data *node)
{
	int	fd2;

	if (str_is_nothing(output))
		return (printf("minishell: : No such file or directory\n"),
			node->last_return = -99, 0);
	fd2 = open(output, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd2 == -1)
	{
		printf("minishell: %s: Permission denied\n", output);
		if (mode == 1)
		{
			ft_free_fds(node);
			ft_exit(node, 1, NULL);
		}
		else
			return (node->last_return = -99, 0);
	}
	if (dup2(fd2, STDOUT_FILENO) == -1)
	{
		ft_free_fds(node);
		ft_exit(node, errno, "dup2 failed");
	}
	close(fd2);
	return (1);
}

int	ft_redirector(t_token *chain, int file_type, int mode, t_data *node)
{
	t_token	*mark1;

	mark1 = chain;
	if (!mark1)
	{
		return (printf("minishell: ambiguous redirect\n"),
			node->last_return = -99, 0);
	}
	if (file_type == INFILE)
		return (redirect_in(mark1->str, mode, node));
	else if (file_type == OUTFILE)
		return (redirect_out(mark1->str, mode, node));
	else if (file_type == OUTFILE_APPEND)
		return (redirect_out_append(mark1->str, mode, node));
	return (1);
}
