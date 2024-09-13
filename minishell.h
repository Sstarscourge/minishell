/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 09:46:09 by fidriss           #+#    #+#             */
/*   Updated: 2024/09/13 11:06:04 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "lib/lib.h"
# include <fcntl.h>

typedef struct s_command 
{
	char				*command;
	char				*full_path;
	char				**args;
	int					arg_count;
	t_list				*input_files;
	t_list				*oa_files;
	t_list				*heredoc_delimiters;
	t_list				*heredoc_content;
	int					pipe_out;
	struct s_command	*next;
}	t_command;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				export;
	struct s_env	*next;
}	t_env;

t_env	*env_fill(char **envp);
int		ft_cd(t_command *cmd, t_list *env);
char	**list_to_pointer(t_env *env);
void	execute_command(t_command *cmd, char **envp, t_env *env);
void	execute_pipeline(t_command *cmd, char **envp, t_env *env);
void	ft_execute(t_command *cmd, char **envp, t_env	*env);
void	write_in_file(char *line);
void	handle_heredoc(t_command *cmd);
void	handle_heredoc_redirections(t_command *cmd);
void	handle_input_redirection(t_list *input_file);
void	handle_output_redirection(t_list *output_files);
void	ft_free_env(char **env);
void	ft_free_command(t_command *cmd);
int		built_in_execution(t_command *cmd, t_env	*env);
int		ft_cd(t_command *cmd, t_list *env);
void	ft_echo(t_command *cmd);
int		ft_env(t_list *env);
int		ft_pwd(t_command *cmd);
int		ft_export(t_command *cmd, t_list *env);
int		ft_unset(t_command *cmd, t_list *env);
void	ft_exit(t_command *cmd);
void	handle_redirections(t_command *current);
void	close_remaining_pipes(int prev_pfd[2], int pfd[2]);
void	create_pipe(int pfd[2]);
void	execute_child_process(t_command *current, t_command *cmd, int pfd[2], int prev_pfd[2], char **envp, t_env *env);
void	execute_parent_process(int prev_pfd[2], int pfd[2]);

#endif