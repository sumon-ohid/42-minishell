/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:46:23 by mhuszar           #+#    #+#             */
/*   Updated: 2024/01/31 18:46:25 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		exit(-1);//error_quit(fd1, 0, NULL);
	close(fd1);
}

void	redirect_out(char *output)
{
	int	fd2;

	//printf("ENTERED OUT\n");
    fd2 = open(output, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (fd2 == -1)
	{
		printf("minishell: %s: Permission denied\n", output);
		exit(1);
	}
	if (dup2(fd2, STDOUT_FILENO) == -1)
		exit(-1);//error_quit(fd2, tomlo, NULL);
	close(fd2);
}

void	redirect_out_append(char *output)
{
	int	fd2;

	fd2 = open(output, O_WRONLY | O_APPEND | O_CREAT , 0644);
	if (fd2 == -1)
	{
		printf("minishell: %s: Permission denied\n", output);
		exit(1);
	}
	if (dup2(fd2, STDOUT_FILENO) == -1)
		exit(-1);//error_quit(fd2, tomlo, NULL);
	close(fd2);
}


void	ft_redirector(t_token *chain, int file_type)
{
    t_token	*mark1;
    
    //printf("ENTERED REDIRECTOR\n");
    //printf("FILE TYPE IS: %d\n", file_type);
    mark1 = chain;
    while (mark1 && mark1->type != file_type)
    {
        //printf("CURRENT FILE TYPE IS: %d\n", mark1->type);
        mark1 = mark1->next;
    }
    if (!mark1)
    {
        //printf("WHOOPS\n");
        exit(-1); //handle error, infile or outfile was not found
    }
    if (file_type == INFILE)
        redirect_in(mark1->str);
    else if (file_type == OUTFILE)
        redirect_out(mark1->str);
    else if (file_type == OUTFILE_APPEND)
        redirect_out_append(mark1->str);
    //printf("NOTHING HAPPENED\n");
}

void	ft_set(t_data *node)
{
	node->std_in = dup(STDIN_FILENO);
	if (node->std_in == -1)
		exit(-1); //error_handling
	node->std_out = dup(STDOUT_FILENO);
	if (node->std_out == -1)
		exit(-1); //error_handling
}

void	ft_restore(t_data *node)
{
	if (dup2(node->std_in, STDIN_FILENO) == -1)
		exit(-1); //error_handling
	if (dup2(node->std_out, STDOUT_FILENO) == -1)
		exit(-1); //error_handling
}

void	ft_redirect_checker(t_token *chain)
{
	t_token	*proxy;

	proxy = chain;
	while(proxy)
	{
		if (proxy->type >= 3 && proxy->type <= 5)
        {
            ft_redirector(chain, proxy->type + 3);
            return ;
        }
        proxy = proxy->next;
	}
}