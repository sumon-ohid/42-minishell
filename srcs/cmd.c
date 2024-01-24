/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:32:03 by msumon            #+#    #+#             */
/*   Updated: 2024/01/19 10:30:40 by msumon           ###   ########.fr       */
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

int	entry_check2(t_token *head, char *line)
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
	return (1);
}

int ft_commander(t_token *chain)
{
	extern char **environ;
	t_token		*mark;

	while (chain && chain->type != COMMAND)
		chain = chain->next;
	mark = chain;
	chain = chain->next;
	while (chain && chain->type == FLAG)
	{
		mark->str = ft_strjoin(mark->str, " ", 1);
		mark->str = ft_strjoin(mark->str, chain->str, 1);
		//malloc protection?
		chain = chain->next;
	}
	extract_find_execute(environ, mark->str, 1);
	exit(-1); //if execve fails
	return (0);
}

int	execute_chain(t_token *chain, char *line)
{
	t_token *proxy;

	proxy = chain;
	if (!chain)
		return (-1);
	while (proxy)
	{
		if (proxy->type == BUILTIN)
			return (entry_check2(chain, line));
		else if (proxy->type == COMMAND)
			return (ft_commander(chain));
		else
			proxy = proxy->next;
	}
	if (!proxy)
		printf("im here to inform you that tokenizer sucks\n");
	return (0);
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

int	exception_checker(t_token **tokens, int processes)
{
	t_token *proxy;

	if (processes != 1)
		return (0);
	proxy = tokens[0];
	while (proxy)
	{
		if (proxy->type == BUILTIN)
			break ;
		while (proxy && proxy->type != BUILTIN)
			proxy = proxy->next;
	}
	if (!proxy)
		return (0);
	else
		return (1);
}

void	executor_init(t_token **tokens, int processes, char *line)
{
	int counter;
	int	pid[512];
	int *status;
	int **fd;

	if (exception_checker(tokens, processes))
	{
		execute_chain(tokens[0], line);
		return ;
	}
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
			//free all the pids if malloced - rn on stack, free token list etc ( - in chain above??)
			exit(1); //kill the child with appropriate return value here
			//exit (-1); //if executing doesnt happen
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
