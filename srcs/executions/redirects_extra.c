/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:02:36 by msumon            #+#    #+#             */
/*   Updated: 2024/02/22 12:04:56 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			ft_exit(node, errno, NULL);
		}
		else
			return (0);
	}
	if (dup2(fd1, STDIN_FILENO) == -1)
		ft_exit(node, errno, "dup2 failed");
	close(fd1);
	return (1);
}

int	redirect_out(char *output, int mode, t_data *node)
{
	int	fd2;

	fd2 = open(output, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (fd2 == -1)
	{
		printf("minishell: %s: Permission denied\n", output);
		if (mode == 1)
		{
			ft_free_fds(node);
			ft_exit(node, errno, NULL);
		}
		else
			return (0);
	}
	if (dup2(fd2, STDOUT_FILENO) == -1)
		ft_exit(node, errno, "dup2 failed");
	close(fd2);
	return (1);
}

int	redirect_out_append(char *output, int mode, t_data *node)
{
	int	fd2;

	fd2 = open(output, O_TRUNC | O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd2 == -1)
	{
		printf("minishell: %s: Permission denied\n", output);
		if (mode == 1)
		{
			ft_free_fds(node);
			ft_exit(node, errno, NULL);
		}
		else
			return (0);
	}
	if (dup2(fd2, STDOUT_FILENO) == -1)
		ft_exit(node, errno, "dup2 failed");
	close(fd2);
	return (1);
}

int	ft_redirector(t_token *chain, int file_type, int mode, t_data *node)
{
	t_token	*mark1;

	mark1 = chain;
	while (mark1 && mark1->type != file_type)
	{
		mark1 = mark1->next;
	}
	if (!mark1)
		ft_exit(node, -1, NULL);
	if (file_type == INFILE)
		return (redirect_in(mark1->str, mode, node));
	else if (file_type == OUTFILE)
		return (redirect_out(mark1->str, mode, node));
	else if (file_type == OUTFILE_APPEND)
		return (redirect_out_append(mark1->str, mode, node));
	return (1);
}
