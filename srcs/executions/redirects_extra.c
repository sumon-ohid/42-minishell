/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:02:36 by msumon            #+#    #+#             */
/*   Updated: 2024/02/07 15:41:35 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect_in(char *input)
{
	int	fd1;

	fd1 = open(input, O_RDONLY);
	if (fd1 == -1)
	{
		printf("minishell: %s: No such file or directory\n", input);
		exit(errno);
	}
	if (dup2(fd1, STDIN_FILENO) == -1)
		exit(-1);
	close(fd1);
}

void	redirect_out(char *output)
{
	int	fd2;

	fd2 = open(output, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (fd2 == -1)
	{
		printf("minishell: %s: Permission denied\n", output);
		exit(1);
	}
	if (dup2(fd2, STDOUT_FILENO) == -1)
		exit(-1);
	close(fd2);
}

void	redirect_out_append(char *output)
{
	int	fd2;

	fd2 = open(output, O_TRUNC | O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd2 == -1)
	{
		printf("minishell: %s: Permission denied\n", output);
		exit(1);
	}
	if (dup2(fd2, STDOUT_FILENO) == -1)
		exit(-1);
	close(fd2);
}

void	ft_redirector(t_token *chain, int file_type)
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
		redirect_in(mark1->str);
	else if (file_type == OUTFILE)
		redirect_out(mark1->str);
	else if (file_type == OUTFILE_APPEND)
		redirect_out_append(mark1->str);
}
