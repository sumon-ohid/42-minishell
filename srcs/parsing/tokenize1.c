/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:57:30 by msumon            #+#    #+#             */
/*   Updated: 2024/02/09 16:33:26 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

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

int	ft_strlen_till_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char *copy_until_char(char *str, char c)
{
	int i;
	char *output;

	i = 0;
	output = malloc(sizeof(char) * ft_strlen_till_char(str, c) + 1);
	if (!output)
		handle_error("malloc in copy_until_char failed", 1);
	while (str[i] && str[i] != c)
	{
		output[i] = str[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

char	*handle_envp(char *str, t_data *node)
{
    char **split_str;
    char *result;
	char *tmp;
	char *new_result;
    int i;

    i = 0;
    result = malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (!result)
        handle_error("malloc in handle_envp failed", 1);
    result[0] = '\0';
    split_str = ft_split(str, ' ', 0, 0);
    if (!split_str)
        handle_error("malloc in handle_envp failed", 1);
    if (ft_strcmp(str, "$?") == 0) //they could be part of a bigger string, should be considered, maybe this should be moved to get_env_value
        return (ft_lastval_str(node));
    if (ft_strcmp(str, "$") == 0)
        return (ft_strdup("$"));
    while (split_str[i])
    {
        if (ft_strstr(split_str[i], "$"))
        {
			tmp = copy_until_char(split_str[i], '$');
			if (tmp) //this part leads to leaks cause of overwriting, check save flags you pass
			{
				new_result = ft_strjoin(result, tmp, 0);
            	result = new_result;
				new_result = ft_strjoin(result, get_env_value(copy_after_char(split_str[i], '$'), node), 0);
            	result = new_result;
				new_result = ft_strjoin(result, " ", 1);
            	result = new_result;
			}
			else
			{
				new_result = ft_strjoin(result, get_env_value(split_str[i], node), 0);
            	result = new_result;
			}
        }
        else
        {
            new_result = ft_strjoin(result, split_str[i], 0);
            result = new_result;
            // new_result = ft_strjoin(result, " ", 1);
            // result = new_result;
        }
        i++;
    }
    ft_free_array(split_str);
    return (result);
}

int	ft_strcat(char *dst, char *src)
{
	int	counter1;
	int	counter2;

	counter1 = 0;
	counter2 = 0;
	printf("dst is: %s, src is: %s\n", dst, src);
	while (dst[counter1])
		counter1++;
	while (src[counter2])
	{
		dst[counter1] = src[counter2];
		counter1++;
		counter2++;
	}
	dst[counter1] = '\0';
	return (counter1);
}
/*
char	*handle_envp(char *str, t_data *node)
{
	char	*output;
	char	tmp[10000];
	char	en_v[1000];
	int		i;
	int 	j;

	j = 0;
	i = 0;
	output = NULL;
	//if (ft_strcmp(str, "$?") == 0)
		//return (ft_lastval_str(node)); MOVE TO GETENV VALUE - it will leak tho
	while (str[i])
	{
		while(str[i] != '$' && str[i])
			tmp[j++] = str[i++];
		tmp[j] = '\0';
		j = 0;
		while(str[i] && str[i] != ' ')
			en_v[j++] = str[i++];
		en_v[j] = '\0';
		printf("tmp is: %s, en_v is: %s\n", tmp, get_env_value(en_v, node));
		j = ft_strcat(tmp, get_env_value(en_v, node));
		while (tmp[j])
			j++;
		printf("after strcat, tmp is: %s\n", tmp);
	}
	tmp[j] = '\0';
	output = ft_strdup(tmp);
	if (!output)
		handle_error("malloc in handle_envp failed", -1);
	return (output);
}*/

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
