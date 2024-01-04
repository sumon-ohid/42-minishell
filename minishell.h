/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:19:30 by mhuszar           #+#    #+#             */
/*   Updated: 2024/01/03 20:19:32 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

//types of data
/*
# define COMMAND 6432

if (seems to be a command)
int type = COMMAND

if type == COMMAND
then
treat it like this*/

//libft_helpers
char	*ft_itoa(int n);
char	**ft_split(char const *str, char c);
int		ft_strstr(const char *big, const char *little);
char	*ft_strjoin(char *s1, char *s2, int save_flag);
int		ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *src);
int		ft_strcmp(char *s1, char *s2);

typedef struct	s_history {
	char 				*string;
	struct s_history	*next;
}				t_history;

#endif
