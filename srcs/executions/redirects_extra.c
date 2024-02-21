/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:02:36 by msumon            #+#    #+#             */
/*   Updated: 2024/02/09 17:01:44 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirect_in(char *input, int mode)
{
	int	fd1;

	fd1 = open(input, O_RDONLY);
	if (fd1 == -1)
	{
		printf("minishell: %s: No such file or directory\n", input);
		if (mode == 1)
			exit(errno);
		else
			return (0);
	}
	if (dup2(fd1, STDIN_FILENO) == -1)
		exit(-1);
	close(fd1);
	return (1);
}

int	redirect_out(char *output, int mode)
{
	int	fd2;

	fd2 = open(output, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (fd2 == -1)
	{
		printf("minishell: %s: Permission denied\n", output);
		if (mode == 1)
			exit(errno);
		else
			return (0);
	}
	if (dup2(fd2, STDOUT_FILENO) == -1)
		exit(-1);
	close(fd2);
	return (1);
}

int	redirect_out_append(char *output, int mode)
{
	int	fd2;

	fd2 = open(output, O_TRUNC | O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd2 == -1)
	{
		printf("minishell: %s: Permission denied\n", output);
		if (mode == 1)
			exit(errno);
		else
			return (0);
	}
	if (dup2(fd2, STDOUT_FILENO) == -1)
		exit(-1);
	close(fd2);
	return (1);
}

int	ft_redirector(t_token *chain, int file_type, int mode)
{
	t_token	*mark1;

	mark1 = chain;
	while (mark1 && mark1->type != file_type)
	{
		mark1 = mark1->next;
	}
	if (!mark1)
	{
		exit(-1);
	}
	if (file_type == INFILE)
		return (redirect_in(mark1->str, mode));
	else if (file_type == OUTFILE)
		return (redirect_out(mark1->str, mode));
	else if (file_type == OUTFILE_APPEND)
		return (redirect_out_append(mark1->str, mode));
	return (1);
}
