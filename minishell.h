/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 09:46:09 by fidriss           #+#    #+#             */
/*   Updated: 2024/09/08 09:23:38 by fidriss          ###   ########.fr       */
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
	char	*command; // The command name (e.g., "echo", "ls")
	char	*full_path; // The full path to the command (e.g., "/bin/echo", "/bin
	char	**args; // Array of arguments including the command
	int		arg_count; // Number of arguments
	t_list	*input_files; // For input redirection (<)
	t_list	*oa_files; // For output redirection (>)
	t_list	*heredoc_delimiters; // For heredoc (<<)
	t_list	*heredoc_content; // Content of heredoc
	int		pipe_out; // 1 if this command pipes to next, 0 otherwise
	struct s_command *next; // Pointer to next command in pipeline
}	t_command;

typedef struct s_env
{
	char *name;
	char *value;
	int export;
	struct s_env *next;
}	t_env;

t_env	*env_fill(char **envp);
int		ft_cd(t_command *cmd, t_list *env);
char	**list_to_pointer(t_env *env);
void	execute_command(t_command *cmd, char **env);
#endif