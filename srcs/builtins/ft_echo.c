/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:25:07 by msumon            #+#    #+#             */
/*   Updated: 2024/02/09 14:23:01 by msumon           ###   ########.fr       */
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
	while (str[i] != c)
		i++;
	i++;
	output = malloc(sizeof(char) * ft_strlen(str + i));
	while (str[i])
	{
		output[j] = str[i];
		i++;
		j++;
	}
	output[j] = '\0';
	return (output);
}

char	*get_env_value(char *arg, t_data *node)
{
	char	*env_value;
	char	*tmp;
	int		i;

	i = 0;
	while (node->envp[i])
	{	
		tmp = copy_until_char(node->envp[i], '=');
		if (ft_strcmp(tmp, arg) == 0)
		{
			env_value = copy_after_char(node->envp[i], '=');
			return (env_value);
		}
		free(tmp);
		i++;
	}
	return ("");
}

void	show_dir(void)
{
	DIR				*d;
	struct dirent	*dir;

	d = opendir(".");
	dir = readdir(d);
	while (dir != NULL)
	{
		if (dir->d_name[0] != '.')
		{
			ft_putstr(dir->d_name);
			ft_putchar(' ');
		}
	}
	closedir(d);
}

void	ft_echo(char *line, t_data *node, t_token *head)
{
	int	fl;
	int	newline;

	newline = 1;
	fl = 0;
	(void)line;
	if (head->next && ft_strcmp(head->next->str, "-n") == 0)
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
