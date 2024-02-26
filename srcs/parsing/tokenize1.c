/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:57:30 by msumon            #+#    #+#             */
/*   Updated: 2024/02/26 15:52:13 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

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
	while (str[i] && str[i] != ' ')
	{
		output[i] = str[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

//TODO: you cannot return itoa and dup directly because if malloc fail considerations, or you have to handle it outside of function
char	*handle_envp(char *str, t_data *node)
{
	char	*result;
	char	*var_name;
	char	*var_value;
	int		i;

	i = 0;
	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!result)
		ft_exit(node, -1, "malloc in handle_envp failed");
	result[0] = '\0';
	while (str[i])
	{
		if(str[i] == '$')
		{
			if (str[i + 1] == '?')
			{
				var_value = ft_lastval_str(node);
				result = ft_strjoin(result, var_value, 1);
				if (!result)
					ft_exit(node, -1, "malloc failed at handle envp");
				free(var_value);
				i++;
			}
			else if (str[i + 1] == '$')
			{
				var_value = ft_itoa(getpid());
				result = ft_strjoin(result, var_value, 1);
				if (!result)
					ft_exit(node, -1, "malloc failed at handle envp");
				free(var_value);
				i++;
			}
			else if ((str[i + 1] >= 'A' && str[i + 1] <= 'Z') || (str[i + 1] >= 'a' && str[i + 1] <= 'z'))
			{
				var_name = extract_var_name(str + i + 1);
				var_value = get_env_value(var_name, node);
				result = ft_strjoin(result, var_value, 1);
				if (!result)
					ft_exit(node, -1, "malloc failed at handle envp");
				i += ft_strlen(var_name);
				free(var_name);
			}
			else
				char_append(&result, str[i]);
		}
		else
			char_append(&result, str[i]);
		i++;
	}
	return (result);
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
