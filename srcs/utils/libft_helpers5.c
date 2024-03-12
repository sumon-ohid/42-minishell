/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_helpers5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:03:01 by msumon            #+#    #+#             */
/*   Updated: 2024/03/12 21:26:02 by mhuszar          ###   ########.fr       */
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
		return (NULL);
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

static int	init(char const *str, char const c)
{
	int	counter;

	counter = 0;
	while (str[counter])
	{
		if (str[counter] == c)
			return (1);
		counter++;
	}
	return (0);
}

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	counter;

	counter = 0;
	if (size <= 0)
		return (ft_strlen(src));
	while (src[counter] != '\0' && counter < (size - 1))
	{
		dst[counter] = src[counter];
		counter++;
	}
	if (counter < size)
		dst[counter] = '\0';
	while (src[counter])
		counter++;
	return (counter);
}

char	*ft_strtrim(char *s1, char *set)
{
	int			counter;
	int			len;
	int			back_count;
	char		*marker;
	char		*result;

	counter = 0;
	len = ft_strlen(s1) - 1;
	back_count = 0;
	while (s1[counter] && init(set, s1[counter]) == 1)
		counter++;
	marker = &s1[counter];
	while (init(set, s1[len]) == 1 && s1[counter])
	{
		back_count++;
		len--;
	}
	result = (char *)malloc(ft_strlen(marker) - back_count + 1);
	if (!result)
		return (0);
	ft_strlcpy(result, marker, ft_strlen(marker) - back_count + 1);
	return (result);
}
