/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:19:30 by mhuszar           #+#    #+#             */
/*   Updated: 2024/02/15 17:49:41 by codespace        ###   ########.fr       */
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
# include <signal.h>

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

//quotes
# define NO_QUOTE 0
# define DOUBLE_QUOTE 1
# define SINGLE_QUOTE 2

extern volatile sig_atomic_t	g_signal;

typedef struct s_token
{
	char			*str;
	int				type;
	char			**arr;
	char			*heredoc_data;
	int				quote;
	struct s_token	*previous;
	struct s_token	*next;
}					t_token;

//internal vars list
typedef struct s_vars
{
	char			*str;
	char			*first_half;
	char			*second_half;
	int				deprecated;
	struct s_vars	*next;
}					t_vars;

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
	//char				*line_for_export;
	int					last_return;
	int					env_len;
	int					**fd;
	int					processes;
	int					*pid;
	int					cur_proc;
	int					std_in;
	int					std_out;
	char				**envp;
	char				*oldpwd;
	char				*pwd;
	char				*home;
	char				*input_line;
	char				*line_temp;
	char				**arr;
	t_vars				*local_vars;
	t_mode				mode;
	t_token				**tokens;
	struct s_data		*next;
}						t_data;

// libft_helpers
char				*ft_itoa(int n);
int					ft_strstr(const char *big, const char *little);
char				*ft_quote_detector(char *big, char *little);
char				*ft_strjoin(char *s1, char *s2, int save_flag);
int					ft_strlen(const char *str);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strdup(const char *src);
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(char *s1, char *s2, size_t n);
char				**ft_split(char const *s, char c, size_t i, size_t j);
char				**ft_split_special(char *s, char c, char mode, size_t j);
int					k_count(char const *s, int i, char c);
void				ft_putstr(char *str);
void				ft_putchar(char c);
char				*ft_strndup(const char *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
char				**ft_malloc(int size, char **str);
char				*ft_strcpy(char *s1, char *s2);
char				**ft_realloc(void *ptr, size_t old_size, size_t new_size);
int					ft_putnbr(int n);
int					ft_strchr(char *str, char c);
int					ft_isspace(int c);
int					ft_isalnum(int c);
char				*ft_itoa(int n);

// heredoc
char				*ft_heredoc(t_data *node, char *str);
void				*ft_realloc_heredoc(void *ptr, size_t old_size,
						size_t new_size);
int					heredocker(char *str);
int					check_for_heredoc(t_data *node, t_token **tokens,
						int processes);
int					heredoc_counter(t_token *tokens);
void				read_from_heredoc(t_token *heredoc);

// builtins
void				ft_cd(char *str, t_data *node);
void				ft_echo(char *line, t_data *node, t_token *head);
void				show_dir(void);
void				print_argument(char *arg, t_data *node);
char				*get_env_value(char *arg, t_data *node);
char				**ft_env(t_data *node);
int					ft_export(t_data *node, t_token *token, char *str);
void				ft_pwd(void);
int					ft_unset(t_data *node, t_token *token, char *str);
char				*ft_getenv(t_data *node, char *str);
void				ft_lastvalue(t_data *node);
char				*ft_lastval_str(t_data *node);
void				ft_exit(t_data *node, int exit_val, char *msg);
void    			ft_localvars(t_token **tokens, t_data *node, int processes);
char 				*copy_until_char(char *str, char c);
char				*copy_after_char(char *str, char c);
void    			ft_localvars(t_token **tokens, t_data *node, int processes);

// take_input
int					entry_check(t_data *node, char *line);
int					ft_lexical_checker(char *line, int in_single_quote,
						int in_double_quote, char prev_char);
char				*ft_upgrade_spaces(char *line, int i, int j, int in_quotes);
t_token				**tokenizer(char *str);
int					pipe_counter(char *str);
char				*handle_envp(char *str, t_data *node);
int					check_builtins(char *word);
int					check_prevs(char *word, int prev_type);
void				process_words(t_token ***origin, char **words, char *str,
						t_data *node);
int					quote_assigner(char *big, char *little);

// cmd01
int					ft_commander(t_token *chain, t_data *node);
int					execute_chain(t_data *node, t_token *chain, char *line,
						int processes);
void				close_what_this_child_doesnt_need(int ***origin, int index,
						int max);
int					exception_checker(t_token **tokens, int processes);
int					executor_init(t_data *node, t_token **tokens, int processes,
						char *line);

// cmd02
char				**parse_input(char *line);
int					entry_check2(t_data *node, t_token *head, char *line);
void				allocate_fd(int ***fd, int processes);
void				fork_processes(int processes, t_data *node,
						t_token **tokens, char *line);

// free memory
void				ft_free_array(char **str);
void				free_tokens(t_token **token, int processes);
void				free_arr(char **arr);
void				error_quit(int fd, int *tomlo, char *str);
char				**free_everything(char **arr, int m_ctr);

// redirections

int					ft_redirector(t_token *chain, int file_type, int mode);
int					ft_redirect_checker(t_token *chain, int mode);
void				ft_set(t_data *node);
void				ft_restore(t_data *node);
void				close_all(int ***origin, int max);

// execution part
char				*extract_path(char *comm2, char **poss_paths,
						char *og_comm);
char				*pathfinder(char **envp, char *comm);
void				extract_find_execute(char **envp, char *full_comm, t_data *node);
void				parent_close(t_data *node, int i, int processes);

// signals
void				mode(t_data *data, t_mode mode);

// handle errors
int					handle_error(char *error, int status);
void				ft_putstr_fd(char *s, int fd);
void				nocomm_error(char *name);

#endif
