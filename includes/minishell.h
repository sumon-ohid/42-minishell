/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:19:30 by mhuszar           #+#    #+#             */
/*   Updated: 2024/01/17 19:29:10 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define GREEN "\033[32m"
# define RESET "\033[0m"

# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

// TOKEN TYPES
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
# define DELIM 11
# define BUILTIN 12

typedef struct s_data
{
	char			*string;
	char			*path;
	struct s_data	*next;
}					t_data;

typedef struct s_token
{
	char			*str;
	int				type;
	char			**arr;
	struct s_token	*previous;
	struct s_token	*next;
}					t_token;

// libft_helpers
char				*ft_itoa(int n);
int					ft_strstr(const char *big, const char *little);
char				*ft_strjoin(char *s1, char *s2, int save_flag);
int					ft_strlen(const char *str);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strdup(const char *src);
int					ft_strcmp(char *s1, char *s2);
char				**ft_split(char const *s, char c, size_t i, size_t j);
void				ft_putstr(char *str);
void				ft_putchar(char c);
char				*ft_strndup(const char *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
char				**ft_malloc(int size, char **str);

// builtins
void				ft_cd(char *str);
void				ft_echo(char *arr);
char				**ft_env(void);
void				ft_export(char *str);
void				ft_pwd(void);
void				ft_unset(char *str);
void 				ft_whoami(void);


// take_input
void				entry_check(char *line);
char				**parse_input(char *line);
t_token				**tokenizer(char *str);
int					pipe_counter(char *str);
char				*handle_envp(char *str);
int					check_builtins(char *word);
int					check_prevs(char *word, int prev_type);
void				process_words(t_token ***origin, char **words, char *str);

// free memory
void				free_tokens(t_token **token);
void				free_arr(char **arr);
void				error_quit(int fd, int *tomlo, char *str);
char				**free_everything(char **arr, int m_ctr);

//execution part
char				*extract_path(char *comm2, char **poss_paths, char *og_comm);
char				*pathfinder(char **envp, char *comm);
void				extract_find_execute(char **envp, char *full_comm, int round);


#endif
