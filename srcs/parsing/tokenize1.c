/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:57:30 by msumon            #+#    #+#             */
/*   Updated: 2024/02/07 15:37:19 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*if (ft_strstr(str, "\""))
 DO SOMETHING HERE!*/

void	ft_free_array(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return ;
}

char	*handle_envp(char *str, t_data *node)
{
	char	*output;

	output = NULL;
	if (ft_strcmp(str, "$?") == 0)
		return (ft_lastval_str(node));
	else if (str[0] == '$')
	{
		if (getenv(str + 1))
			output = ft_strdup(getenv(str + 1));
		else
			output = ft_strdup("");
	}
	if (!output)
		exit(EXIT_FAILURE);
	return (output);
}

int	check_builtins(char *word)
{
	if (!word)
		return (-1);
	else if (ft_strcmp(word, "cd") == 0)
		return (0);
	else if (ft_strcmp(word, "echo") == 0)
		return (0);
	else if (ft_strcmp(word, "env") == 0)
		return (0);
	else if (ft_strcmp(word, "clear") == 0)
		return (0);
	else if (ft_strcmp(word, "pwd") == 0)
		return (0);
	else if (ft_strcmp(word, "exit") == 0)
		return (0);
	else if (ft_strcmp(word, "export") == 0)
		return (0);
	else if (ft_strcmp(word, "unset") == 0)
		return (0);
	else
		return (-1);
}

int	check_assign(char *word)
{
	int	counter;

	counter = 0;
	if (!word)
		return (0);
	while (word[counter])
	{
		if (word[counter] == '=')
			return (1);
		counter++;
	}
	return (0);
}

int	check_prevs(char *word, int prev_type)
{
	if (!word)
		return (0);
	else if (check_assign(word))
		return (SET);
	else if (prev_type == HEREDOC)
		return (DELIM);
	else if (prev_type == REDIR_OUT)
		return (OUTFILE);
	else if (prev_type == REDIR_OUT_APPEND)
		return (OUTFILE_APPEND);
	else if (prev_type == REDIR_IN)
		return (INFILE);
	else if (prev_type == BUILTIN || prev_type == COMMAND || prev_type == FLAG)
		return (FLAG);
	else
		return (COMMAND);
}
