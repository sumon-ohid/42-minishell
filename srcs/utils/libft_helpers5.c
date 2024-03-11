/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_helpers5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:03:01 by msumon            #+#    #+#             */
/*   Updated: 2024/03/11 22:29:08 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_quote(char *str)
{
	int		i;
	int		j;
	char	*output;

	i = 0;
	j = 0;
	output = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!output)
		return (0);
	while (str[i])
	{
		if (str[i] != '\"' && str[i] != '\'')
		{
			output[j] = str[i];
			j++;
		}
		i++;
	}
	output[j] = '\0';
	return (output);
}

void	close_all(int ***origin, int max)
{
	int	**fd;
	int	counter;

	fd = *origin;
	counter = 0;
	while (counter < max)
	{
		if (fd[counter][0] != -1)
		{
			close(fd[counter][0]);
			fd[counter][0] = -1;
		}
		if (fd[counter][1] != -1)
		{
			close(fd[counter][1]);
			fd[counter][1] = -1;
		}
		counter++;
	}
}

void	env_quit(char **result, t_data *node)
{
	if (result)
		ft_free_array(result);
	free(node);
	handle_error("env preparation failed", -1);
}
