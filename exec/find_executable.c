/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 18:50:57 by fidriss           #+#    #+#             */
/*   Updated: 2024/10/14 16:58:36 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_directory(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		print_error("Is a directory", path);
		exit(126);
	}
}

char	*construct_full_path(t_command *cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	pwd = ft_strjoin(pwd, "/", 0);
	cmd->full_path = ft_strjoin(pwd, cmd->command, 1);
	check_directory(cmd->full_path);
	return (cmd->full_path);
}

void	execute_and_handle_errors(t_command *cmd, char **envp)
{
	if (access(cmd->full_path, X_OK) == 0)
	{
		if (execve(cmd->full_path, cmd->argsp, envp) == -1)
		{
			free(cmd->full_path);
			free_array(envp);
			exit(1);
		}
	}
	else if (access(cmd->full_path, F_OK) == 0)
	{
		free(cmd->full_path);
		cmd->full_path = NULL;
		print_error("Permission denied.", cmd->command);
		free_array(envp);
		exit(126);
	}
	print_error("No such file or directory.", cmd->command);
	free(cmd->full_path);
	exit(127);
}

void	check_bin(t_command *cmd, char **envp)
{
	cmd->full_path = construct_full_path(cmd);
	if (cmd->full_path == NULL)
		return ;
	execute_and_handle_errors(cmd, envp);
}
