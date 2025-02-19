/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:33:05 by fidriss           #+#    #+#             */
/*   Updated: 2024/10/14 21:17:09 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/stat.h>

typedef struct s_operate
{
	int					sgl_quote;
	int					dbl_quote;
}						t_operat;

typedef struct s_pfds
{
	int					prev_pfd[2];
	int					pfd[2];
}						t_pfds;

enum					e_token
{
	WORD = -1,
	WHITE_SPACE = 2,
	NEW_LINE = '\n',
	QOUTE = '\'',
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	APPEND,
	DREDIR_OUT,
	_NULL = '0',
	FLAG,
	ER,
};

enum					e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
	NGENERAL,
};

enum					e_type
{
	APP,
	OUT_FILE,
};

typedef struct s_elem
{
	char				*content;
	enum e_token		type;
	enum e_state		state;
	struct s_elem		*next;
}						t_elem;

typedef struct s_list
{
	char				*content;
	int					type;
	int					state;
	struct s_list		*next;
}						t_list;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_command
{
	char				*command;
	char				*full_path;
	t_list				*args;
	char				**argsp;
	int					arg_count;
	t_list				*input_files;
	t_list				*oa_files;
	char				*heredoc_content;
	t_list				*heredoc_delimiters;
	int					pipe_out;
	int					exit_status;
	struct s_command	*next;
}						t_command;

typedef struct s_pipeline
{
	t_pfds				*pfds;
	int					*pids;
	t_command			*current;
	int					i;
	int					original_stdin;
}						t_pipeline;

typedef struct s_utile
{
	char				*new_str;
	char				*returnstr;
	char				*str;
	int					i;
	t_command			*cmd;
	t_command			*cr;
	t_elem				*current;
}						t_utile;

int						g_signal;
void					check_directory(char *path);
int						ft_lstcmdsize(t_command *lst);
int						check_special_characters(char *str);
void					combine(t_elem **elm);
void					lexer_space(t_elem **elem, int *i);
void					lexer_quote(t_elem **elem, int *i, char *str);
void					lexer_redirin(t_elem **elem, int *i, char *str);
void					lexer_utile(t_elem **elem, int *i, char *str);
void					lexer_pipe(t_elem **elem, int *i);
void					lexer_flag(t_elem **elem, int *i, char *str);
void					lexer_redirout(t_elem **elem, int *i, char *str);
void					parse_command_in(t_command *cmd, t_elem *current);
void					parse_command_flag(t_command *cmd, t_elem *current);
void					parse_command_redirout(t_command *cmd,
							t_elem **current);
void					parse_command_redir_in(t_command *cmd,
							t_elem **current);
void					parse_command_heredoc(t_command *cmd, t_elem **current);
void					parse_command_pipe(t_command **cmd);
void					cmpl_pars(t_command *cr, t_elem **elem);
t_command				*new_command(void);
void					ft_lstclear_cmd(t_command **cmd);
void					parse_command_redirout_utile(t_command *cmd,
							t_elem **current, int i);
void					sighdl2(int sig);
void					wait_for_processes(int *pids,
							int count, int *exit_status);
void					handle_child_process(t_command *current, t_pfds *pfds,
							char **envp, t_env **env);
int						ft_isalnum(int c);
void					ft_clear_command(t_command **cmd);
int						check_existing_node(t_env *env, char *arg);
void					print_export(t_env *env);
t_env					*create_new_node(char *arg);
char					*expand_line(char *line, t_env *env, t_command *cmd);
char					*ft_itoa(int n);
void					combine(t_elem **elm);
int						is_builtin(char *cmd);
long long				ft_atoi(const char *str);
void					print_error(char *str, char *command);
void					fill_args(t_command *cmd);
char					**ft_split(char *s, char c);
char					*is_execute(char *commd, char **envp, t_env **env);
char					**list_to_char(t_list *arg_list);
char					*ft_strchr(char *s, int c);
int						ft_strncmp(char *s1, char *s2, size_t n);
void					ft_putstr_fd(char *s, int fd);
void					ft_lstclear_list(t_list **head);
void					ft_lstclear_envp(t_env **env);
void					ft_lstclear_cmd(t_command **cmd);
t_command				*parse_command(t_elem *elem);
int						ft_isalpha(char c);
char					*ft_strchrr(char *str, char c);
void					ft_strncpy(char *dst, char *src, size_t len);
int						ft_strcmp(char *s1, char *s2);
t_env					*env_fill(char **envp);
void					expand(t_elem *elem, t_env *env, int exit_status);
t_elem					*lexer_command(char *str);
char					*ft_strtrim(char *s1, char *set);
size_t					ft_strlen(char *s);
char					*ft_strjoin(char *s1, char *s2, int flag);
void					free_array(char **array);
int						skip_quote(char *line, char quote_type);
char					*ft_substr(char *s, unsigned int start, size_t len);
t_list					*eenv_fill(char **envp);
t_list					*ft_lstlast(t_list *lst);
void					ft_lstadd_back(t_list **lst, t_list *new);
t_list					*ft_lstnew(void *content);
char					**ft_split(char *s, char c);
char					*ft_strdup(char *s1);
char					**set_free(char **res, size_t i);
void					*ft_memcpy(void *dst, void *src, size_t n);
t_elem					*ft_lstnew_elem(char *content);
void					ft_lstadd_back_elem(t_elem **lst, t_elem *new);
t_elem					*ft_lstlast_elem(t_elem *lst);
t_elem					*elem_fill(char **p);
char					*check_error(char *line, int *exit_status);
void					ft_lstclear_elem(t_elem **head);
t_env					*env_fill(char **envp);
char					**list_to_pointer(t_env *env);
void					execute_command(t_command *cmd, char **envp,
							t_env **env, int *exit_status);
void					execute_pipeline(t_command *cmd, char **envp,
							t_env **env, int *exit_status);
void					ft_execute(t_command *cmd, char **envp,
							t_env **env, int *exit_status);
void					write_in_file(char *line, int fd);
void					handle_heredoc(t_command *cmd, t_env *env, int flag);
void					handle_heredoc_redirections(t_command *cmd, t_env *env,
							int flag);
int						handle_input_redirection(t_list *input_file, int flag);
int						handle_output_redirection(t_list *output_files,
							int flag);
void					ft_free_env(char **env);
void					built_in_execution(t_command *cmd, t_env **env);
void					close_remaining_pipes(t_pipeline *pipeline);
void					create_pipe(int pfd[2]);
void					execute_child_process(t_command *current, t_pfds *pfds,
							char **envp, t_env *env);
int						execute_parent_process(t_pfds *pfds);
t_env					*find_node(t_env *env, char *name);
void					delete_node(t_env *env_tmp, t_env **env);
size_t					count_words(char *s, char del);
char					*before_equal_sign(char *string);
char					*after_equal_sign(char *string);
void					add_env(t_env **env, t_env *node);
int						ft_echo(t_command *cmd);
int						ft_pwd(t_env **env);
int						ft_export(t_command *cmd, t_env **env);
int						ft_unset(t_command *cmd, t_env **env);
int						ft_env(t_env **env);
void					ft_exit(t_command *cmd);
int						ft_cd(t_command *cmd, t_env **env);
void					handle_sigint(int sig);
int						ft_isdigit(char c);
char					*beforedolaar(char *str, int *j);
char					*makestring(char c);
char					*env_string(char *str, t_env *env);
int						is_special(char c);
int						skip_quote(char *line, char quote_type);
char					*print_syntax_error(char *line, int *exit_status);
int						checking_quotes(int *op, char *line, int i, char quote);
t_operat				check_quotes(char *line);
void					check_bin(t_command *cmd, char **envp);
void					sighandle(int sig);
t_pfds					*initialize_pfd(void);
void					handle_signal_exit_status(int signum, int *exit_status);
void					sighdl(int sig);
int						ft_lstsize(t_list *lst);
size_t					wordlen(char *s, char c);
char					**allocate_args(t_list *arg_list);
void					free_args(char **args, int i);
void					execute_builtin_command(t_command *current,
							t_env **env, int *exit_stat);
void					handle_built_in(t_command *current, t_env **env);

#endif