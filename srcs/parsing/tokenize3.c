/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:06:20 by msumon            #+#    #+#             */
/*   Updated: 2024/02/29 11:40:51 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*if (ft_strstr(str, "\""))
 DO SOMETHING HERE!*/
char	*extract_var_name(char *str)
{
	int		i;
	char	*output;

	i = 0;
	output = malloc(sizeof(char) * (ft_strlen_till_char(str, ' ') + 1));
	if (!output)
		handle_error("malloc in extract_var_name failed", 1);
	while (str[i] && str[i] != ' ' && str[i] != '$')
	{
		output[i] = str[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

char	*handle_dollar_question(char *result, t_data *node, int *i)
{
	char	*var_value;

	var_value = ft_lastval_str(node);
	result = ft_strjoin(result, var_value, 1);
	if (!result)
		ft_exit(node, -1, "malloc failed at handle envp");
	free(var_value);
	(*i)++;
	return (result);
}

char	*handle_dollar_dollar(char *result, t_data *node, int *i)
{
	char	*var_value;

	var_value = ft_itoa(getpid());
	result = ft_strjoin(result, var_value, 1);
	if (!result)
		ft_exit(node, -1, "malloc failed at handle envp");
	free(var_value);
	(*i)++;
	return (result);
}

char	*handle_env_values(char *str, char *result, t_data *node, int *i)
{
	char	*var_name;
	char	*var_value;

	if ((str[(*i) + 1] >= 'A' && str[(*i) + 1] <= 'Z') || (str[(*i) + 1] >= 'a'
			&& str[(*i) + 1] <= 'z'))
	{
		var_name = extract_var_name(str + (*i) + 1);
		var_value = get_env_value(var_name, node);
		result = ft_strjoin(result, var_value, 1);
		if (!result)
			ft_exit(node, -1, "malloc failed at handle envp");
		(*i) += ft_strlen(var_name);
		free(var_name);
	}
	else
		char_append(&result, str[(*i)]);
	return (result);
}

char	*handle_envp(char *str, t_data *node)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!result)
		ft_exit(node, -1, "malloc in handle_envp failed");
	result[0] = '\0';
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
				result = handle_dollar_question(result, node, &i);
			else if (str[i + 1] == '$')
				result = handle_dollar_dollar(result, node, &i);
			else if (str[i + 1] == '-')
			{
				printf("I knew it, Don't go this much crazy!\n");
				i++;
			}
			else
				result = handle_env_values(str, result, node, &i);
		}
		else
			char_append(&result, str[i]);
		i++;
	}
	return (result);
}
