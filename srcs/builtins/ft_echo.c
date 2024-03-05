/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:25:07 by msumon            #+#    #+#             */
/*   Updated: 2024/03/05 11:32:36 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*copy_after_char(char *str, char c)
{
	int		i;
	int		j;
	char	*output;

	i = 0;
	j = 0;
	if (ft_strchr(str, c) == 0)
		return (ft_strdup(""));
	while (str[i] != c)
		i++;
	i++;
	output = malloc(sizeof(char) * ft_strlen(str + i) + 1);
	if (!output)
		return (NULL);
	while (str[i])
	{
		output[j] = str[i];
		i++;
		j++;
	}
	output[j] = '\0';
	return (output);
}

void	remove_many_spaces(char *envp)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * ft_strlen(envp) + 1);
	if (!tmp)
		return ;
	while (envp[i])
	{
		if (envp[i] == ' ' && envp[i + 1] == ' ')
			i++;
		else
		{
			tmp[j] = envp[i];
			i++;
			j++;
		}
	}
	tmp[j] = '\0';
	ft_strcpy(envp, tmp);
	free(tmp);

}

char	*get_env_value(char *arg, t_data *node)
{
	char	*env_value;
	char	*tmp;
	int		i;

	i = 0;
	while (node->envp[i])
	{
		remove_many_spaces(node->envp[i]);
		tmp = copy_until_char(node->envp[i], '=');
		if (!tmp)
			ft_exit(node, 127, "malloc error in get_env");
		if (ft_strcmp(tmp, arg) == 0)
		{
			if (node->envp[i][ft_strlen(tmp)] == '=')
				env_value = node->envp[i] + ft_strlen(tmp) + 1;
			else if (node->envp[i][ft_strlen(tmp)] == '\0')
				env_value = "";
			else
				env_value = arg;
			free(tmp);
			return (env_value);
		}
		free(tmp);
		i++;
	}
	return ("");
}

int flag_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	ft_echo(char *line, t_data *node, t_token *head)
{
	int	fl;
	int	newline;

	newline = 1;
	fl = 0;
	(void)line;
	if (head->next && flag_check(head->next->str))
	{
		newline = 0;
		head = head->next->next;
	}
	while (head)
	{
		if (head->type == FLAG)
		{
			if (fl)
				ft_putchar(' ');
			print_argument(head->str, node);
			fl = 1;
		}
		head = head->next;
	}
	if (newline)
		ft_putchar('\n');
}
