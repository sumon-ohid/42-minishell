/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon <msumon@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:24:36 by msumon            #+#    #+#             */
/*   Updated: 2024/03/12 17:31:45 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	change_directory(char *str, t_data *node)
{
	if (str == NULL)
	{
		node->home = ft_getenv("HOME", node);
		if (node->home == NULL)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			node->last_return = -99;
			return (1);
		}
		else
			chdir(node->home);
		return (0);
	}
	else if (ft_strcmp(str, "-") == 0)
	{
		chdir(node->oldpwd);
		printf("%s\n", node->oldpwd);
		return (0);
	}
	else if (chdir(str) == -1)
	{
		ft_putstr_fd("minishell: cd: no such file or directory\n", 2);
		return (node->last_return = -99, 1);
	}
	return (0);
}

int	handle_oldpwd_null(t_data *node, char *str, char *pwd, char *line)
{
	int	ret;

	ret = 0;
	ft_unsetenv(node, "OLDPWD");
	node->old_turn = 1;
	free(node->oldpwd);
	node->oldpwd = get_current_directory();
	if (!node->oldpwd)
		return (-1);
	ret = change_directory(str, node);
	free(pwd);
	free(line);
	return (ret);
}

int	handle_oldpwd_null_old_turn(t_data *node, char *str, char *pwd, char *line)
{
	int	ret;
	int	var_exists;

	var_exists = 0;
	ret = 0;
	line = ft_strjoin("OLDPWD=", node->oldpwd, 0);
	if (!line)
		ft_exit(node, -1, "malloc failed in handle_oldpwd_null_old_turn");
	var_exists = check_if_var_exists(node, line);
	if (var_exists)
	{
		if (handle_var_exist_in_envp(node, line) == -1)
			ft_exit(node, -1, "malloc failed in handle_oldpwd_null_old_turn");
	}
	else
		handle_var_not_exists(node, line);
	ret = change_directory(str, node);
	free(node->oldpwd);
	node->oldpwd = get_current_directory();
	if (!node->oldpwd)
		return (-1);
	free(pwd);
	free(line);
	return (ret);
}

int	ft_cd(char *str, t_data *node)
{
	char	*oldpwd;
	char	*pwd;
	int		ret;
	char	*line;

	ret = 0;
	pwd = NULL;
	line = NULL;
	oldpwd = ft_getenv("PWD", node);
	if (oldpwd == NULL && !(node->old_turn))
		return (handle_oldpwd_null(node, str, pwd, line));
	if (oldpwd == NULL && node->old_turn == 1)
		return (handle_oldpwd_null_old_turn(node, str, pwd, line));
	ret = change_directory(str, node);
	pwd = get_current_directory();
	if (pwd == NULL)
		return (-1);
	ft_setenv(node, "OLDPWD", oldpwd);
	ft_setenv(node, "PWD", pwd);
	free(pwd);
	return (ret);
}

// int	ft_cd(char *str, t_data *node)
// {
// 	char	*oldpwd;
// 	char	*pwd;
// 	int		ret;
// 	char	*line;
// 	int		var_exists;

// 	var_exists = 0;
// 	ret = 0;
// 	pwd = NULL;
// 	line = NULL;
// 	oldpwd = ft_strdup(ft_getenv("PWD", node));
// 	if (oldpwd == NULL && !(node->old_turn))
// 	{
// 		ft_unsetenv(node, "OLDPWD");
// 		node->old_turn = 1;
// 		free(node->oldpwd);
// 		node->oldpwd = get_current_directory();
// 		ret = change_directory(str, node);
// 		free(pwd);
// 		free(line);
// 		return (ret);
// 	}
// 	if (oldpwd == NULL && node->old_turn == 1)
// 	{
// 		line = ft_strjoin("OLDPWD=", node->oldpwd, 0); //need to protect & free
// 		var_exists = check_if_var_exists(node, line);
// 		if (var_exists)
// 			handle_var_exist_in_envp(node, line);
// 		else
// 			handle_var_not_exists(node, line);
// 		ret = change_directory(str, node);
// 		free(node->oldpwd);
// 		node->oldpwd = get_current_directory();
// 		free(pwd);
// 		free(line);
// 		return (ret);
// 	}
// 	ret = change_directory(str, node);
// 	pwd = get_current_directory();
// 	if (pwd == NULL)
// 		ft_exit(node, -1, "getcwd failed");
// 	ft_setenv(node, "OLDPWD", oldpwd);
// 	ft_setenv(node, "PWD", pwd);
// 	free(pwd);
// 	free(oldpwd);
// 	return (ret);
// }
