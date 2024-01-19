/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:32:03 by msumon            #+#    #+#             */
/*   Updated: 2024/01/18 08:09:54 by msumon           ###   ########.fr       */
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
		exit(127);
	else if (ft_strcmp(head->str, "exit") == 0)
		exit(0);
	else if (ft_strcmp(head->str, "ls") == 0)
		ft_ls(".");
	else
		printf("%s : command not found.\n", line);
}

void	execute_chain(t_token *chain, char *line)
{
	if (chain)
	{
		if (chain->type == BUILTIN)
		{
			entry_check2(chain, line);
		}
	}
	else
		printf("im here to inform you that tokenizer sucks\n");
}

void close_what_this_child_doesnt_need(int ***origin, int index, int max)
{
	int **fd;
	int counter;

	fd = *origin;
	counter = 0;
	while (counter < index - 1)
	{
		close(fd[counter][0]);
		close(fd[counter][1]);
		counter++;
	}
	if (index != 0)
		close(fd[counter][1]);
	counter++;
	if (index != max)
		close(fd[counter][0]);
	counter++;
	while (counter <= max)
	{
		close(fd[counter][0]);
		close(fd[counter][1]);
		counter++;
	}
}

void	executor_init(t_token **tokens, int processes, char *line)
{
	int counter;
	int	pid[512];
	int *status;
	int **fd;

	counter = 0; //will stand for current process
	fd = malloc(sizeof(int *) * (processes - 1)); //pipes (arrays of size 4*2) for each child-child communication
	//pid = malloc(sizeof(int) * processes); //pid tracker for each child
	while (counter < processes - 1)
	{
		fd[counter] = malloc(sizeof(int) * 2);
		if (pipe(fd[counter]) == -1)
			return ; //error handling!
		counter++;
	}
	counter = 0;
	while (counter < processes)
	{
		pid[counter] = fork();
		if (pid[counter] == 0) //i'm the child
		{
			if (counter != 0) //i'm not the first child, which reads from STDIN
				dup2(fd[counter - 1][0], STDIN_FILENO);
			if (counter != processes - 1) //i'm not the last child, which writes to STDOUT
				dup2(fd[counter][1], STDOUT_FILENO);
			close_what_this_child_doesnt_need(&fd, counter, processes - 1);
			execute_chain(tokens[counter], line);
			//free all the pids if malloced - rn on stack
			exit (-1); //if executing doesnt happen
		}
		else if (pid[counter] == -1)
		{
			//forking error happened! Idk how to handle it yet.
		}
		counter++;
	}
	counter = 0;
	status = malloc(sizeof(int) * processes); //status tracker for each child
	while (counter < processes)
	{
		waitpid(pid[counter], &status[counter], 0);
		counter++;
	}
	return ;
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
	//write(2, "SO far so good\n", 15);
	executor_init(tokens, pipe_counter(line), line);
	//free_tokens(tokens);
	free(line);
}
