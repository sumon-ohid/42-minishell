/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:46:56 by msumon            #+#    #+#             */
/*   Updated: 2024/03/12 13:46:22 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_for_processes(int *pid, int *status, int processes, t_data *node)
{
	int	counter;
	int	return_val;

	counter = 0;
	while (counter < processes)
	{
		return_val = waitpid(pid[counter], &status[counter], WNOHANG);
		if (return_val == -1)
			ft_exit(node, 127, "error in execution part");
		else if (return_val == 0)
		{
			if (g_signal == CTRL_C)
				kill(pid[counter], SIGINT);
			g_signal = 0;
		}
		else
		{
			if (WIFSIGNALED(status[counter]) && WTERMSIG(status[counter]) == 3)
				ft_printerr("Quit (core dumped)\n");
			else if (WIFSIGNALED(status[counter]) && counter == processes - 1
				&& node->mode != HEREDOC)
				write(STDOUT_FILENO, "\n", 1);
			counter++;
		}
	}
}
