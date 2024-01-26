/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:00:50 by msumon            #+#    #+#             */
/*   Updated: 2024/01/26 18:02:28 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_signal = 0;

void	handler(int status)
{
    if (status == SIGINT)
    {
        g_signal = CTRL_C;
        ioctl(0, TIOCSTI, "\n");
		//rl_replace_line("", 0);
        rl_on_new_line();
    }
}

void	handle_heredoc(int status)
{
	if (status == SIGINT)
	{
		g_signal = CTRL_C;
		ioctl(0, TIOCSTI, "\n");
		//rl_replace_line("", 0); 
		rl_on_new_line();
	}
}

void	signal_init(t_data *data)
{
	if (data->mode == INTERACTIVE)
	{
		signal(SIGINT, &handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (data->mode == NON_INTERACTIVE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (data->mode == CHILD)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (data->mode == HEREDOCS)
	{
		signal(SIGINT, &handle_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	mode(t_data *data, t_mode mode)
{
	data->mode = mode;
	signal_init(data);
}
