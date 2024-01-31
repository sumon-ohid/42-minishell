/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msumon < msumon@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:19:30 by mhuszar           #+#    #+#             */
/*   Updated: 2024/01/26 17:33:58 by msumon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define GREEN "\033[32m"
# define RESET "\033[0m"

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
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
# define SET 13

// signals
# define CTRL_C 1
# define CTRL_D 2

typedef struct s_token
{
	char			*str;
	int				type;
	char			**arr;
	struct s_token	*previous;
	struct s_token	*next;
}					t_token;

// signal mode
typedef enum s_mode
{
	INTERACTIVE,
	NON_INTERACTIVE,
	CHILD,
	HEREDOCS
}					t_mode;

typedef struct s_data
{
	char			*line_for_export;
	int				env_len;
	int				**fd;
	int				processes;
	int				*pid;
	char			**envp;
	char			*oldpwd;
	char			*pwd;
	char			*home;
	t_mode			mode;
	t_token			*tokens;
	struct s_data	*next;
}					t_data;

// libft_helpers
char				*ft_itoa(int n);
int					ft_strstr(const char *big, const char *little);
char				*ft_strjoin(char *s1, char *s2, int save_flag);
int					ft_strlen(const char *str);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strdup(const char *src);
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(char *s1, char *s2, size_t n);
char				**ft_split(char const *s, char c, size_t i, size_t j);
void				ft_putstr(char *str);
void				ft_putchar(char c);
char				*ft_strndup(const char *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
char				**ft_malloc(int size, char **str);
char				*ft_strcpy(char *s1, char *s2);
char				**ft_realloc(void *ptr, size_t old_size, size_t new_size);
void				*ft_realloc_heredoc(void *ptr, size_t old_size,
						size_t new_size);
int					ft_putnbr(int n);
int					ft_strchr(char *str, char c);
int					ft_isspace(int c);
int					ft_isalnum(int c);

// builtins
void				ft_cd(char *str, t_data *node);
void				ft_echo(char *line, t_data *node);
char				**ft_env(t_data *node);
int					ft_export(t_data *node, t_token *token, char *str);
void				ft_pwd(void);
int					ft_unset(t_data *node, t_token *token, char *str);
char				*ft_getenv(t_data *node, char *str);

// take_input

int					entry_check(t_data *node, char *line);
t_token				**tokenizer(char *str);
int					pipe_counter(char *str);
char				*handle_envp(char *str);
int					check_builtins(char *word);
int					check_prevs(char *word, int prev_type);
void				process_words(t_token ***origin, char **words, char *str);

// cmd01
int					ft_commander(t_token *chain);
int					execute_chain(t_data *node, t_token *chain, char *line, int processes);
void				close_what_this_child_doesnt_need(int ***origin, int index,
						int max);
int					exception_checker(t_token **tokens, int processes);

// cmd02
char				**parse_input(char *line);
int					entry_check2(t_data *node, t_token *head, char *line);
void				allocate_fd(int ***fd, int processes);
void				fork_processes(int processes, t_data *node,
						t_token **tokens, char *line);

// free memory
void				free_tokens(t_token **token);
void				free_arr(char **arr);
void				error_quit(int fd, int *tomlo, char *str);
char				**free_everything(char **arr, int m_ctr);

// execution part
char				*extract_path(char *comm2, char **poss_paths,
						char *og_comm);
char				*pathfinder(char **envp, char *comm);
void				extract_find_execute(char **envp, char *full_comm,
						int round);

// signals
void				mode(t_data *data, t_mode mode);

#endif
