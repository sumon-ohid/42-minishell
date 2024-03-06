/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd03.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:46:56 by msumon            #+#    #+#             */
/*   Updated: 2024/03/06 16:47:50 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_wait_and_signal(int *pid, int *status, int counter, t_data *node)
{
	int	return_val;

	return_val = waitpid(pid[counter], &status[counter], WNOHANG);
	if (return_val == -1)
		ft_exit(node, 127, "error in execution part");
	else if (return_val == 0)
	{
		if (g_signal == CTRL_C)
		{
			kill(pid[counter], SIGINT);
			g_signal = 0;
		}
	}
}

void	handle_status_and_counter(int *status, int counter, int processes,
		t_data *node)
{
	if (WIFSIGNALED(status[counter]) && WTERMSIG(status[counter]) == 3)
		printf("Quit (core dumped)\n");
	else if (WIFSIGNALED(status[counter]) && counter == processes - 1
		&& node->mode != HEREDOC)
		write(STDOUT_FILENO, "\n", 1);
	if (WIFEXITED(status[counter]) || WIFSIGNALED(status[counter]))
		counter++;
}

void	wait_for_processes(int *pid, int *status, int processes, t_data *node)
{
	int	counter;

	counter = 0;
	while (counter < processes)
	{
		handle_wait_and_signal(pid, status, counter, node);
		handle_status_and_counter(status, counter, processes, node);
	}
}
