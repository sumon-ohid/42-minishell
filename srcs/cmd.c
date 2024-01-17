/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:32:03 by msumon            #+#    #+#             */
/*   Updated: 2024/01/17 19:36:29 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <dirent.h>

void	ft_ls(char *dir_name)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(dir_name);
	if (!dir)
	{
		perror("minishell");
		return ;
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			ft_putstr(entry->d_name);
			ft_putchar(' ');
		}
		entry = readdir(dir);
	}
	ft_putchar('\n');
	closedir(dir);
}

char	**parse_input(char *line)
{
	char	**tokens;

	tokens = ft_split(line, ' ', 0, 0);
	if (!tokens)
	{
		write(2, "Allocation error\n", 17);
		exit(EXIT_FAILURE);
	}
	return (tokens);
}

void	entry_check2(t_token *head, char *line)
{
	if (ft_strcmp(head->str, "whoami") == 0)
		printf("%s\n", getenv("USER"));
	else if (ft_strcmp(head->str, "cd") == 0)
		ft_cd(head->next->str);
	else if (ft_strcmp(head->str, "echo") == 0)
		ft_echo(line);
	else if (ft_strcmp(head->str, "env") == 0)
		ft_env();
	else if (ft_strcmp(head->str, "clear") == 0)
		write(1, "\033[H\033[J", 6);
	else if (ft_strcmp(head->str, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(head->str, "exit") == 0)
		exit(0);
	else if (ft_strcmp(head->str, "exit") == 0)
		exit(0);
	else if (ft_strcmp(head->str, "ls") == 0)
		ft_ls(".");
	else
		printf("%s : command not found.\n", line);
}

void	executor(t_token **tokens, int processes, char *line)
{
	// ima execute shit here but now 
	//let's just check for builtins in a simple way
	(void)processes;
	// printf("entered executor\n");
	if (*tokens)
	{
		if (tokens[0]->type == BUILTIN)
			entry_check2(tokens[0], line);
	}
	else
		printf("im here to inform you that tokenizer sucks\n");
}

void	entry_check(char *line)
{
	char	**arr;
	t_token	**tokens;

	tokens = ft_calloc(sizeof(t_token *), pipe_counter(line));
	arr = parse_input(line);
	if (!arr)
		return ;
	process_words(&tokens, arr, line);
	executor(tokens, pipe_counter(line), line);
	free_tokens(tokens);
	free(line);
}
