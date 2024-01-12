/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumon <sumon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:19:30 by mhuszar           #+#    #+#             */
/*   Updated: 2024/01/12 11:51:44 by sumon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define GREEN "\033[32m"
#define RESET "\033[0m"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <stddef.h>
# include <stdarg.h>


//TOKEN TYPES
# define COMMAND 1
# define FLAG 2
# define REDIR_IN 3
# define REDIR_OUT 4
# define REDIR_OUT_APPEND 5
# define INFILE 6
# define OUTFILE 7
# define OUTFILE_APPEND 8
# define PIPE 9
# define HEREDOC 10

typedef struct	s_data
{
	char 				*string;
	char				*path;
	struct s_data	*next;
}				t_data;

typedef struct	s_token
{
	char 				*str;
	int					type;
	struct s_token		*previous;
	struct s_token		*next;
}			t_token;

//libft_helpers
char	*ft_itoa(int n);
int		ft_strstr(const char *big, const char *little);
char	*ft_strjoin(char *s1, char *s2, int save_flag);
int		ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *src);
int 	ft_strcmp(char *s1, char *s2);
char	**ft_split(char const *s, char c, size_t i, size_t j);
void	ft_putstr(char *str);
void	ft_putchar(char c);
char	*ft_strndup(const char *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);

//others
void	entry_check(char *str, char *line);
char	**parse_input(char *line);
t_token **tokenizer(char *str);

#endif
