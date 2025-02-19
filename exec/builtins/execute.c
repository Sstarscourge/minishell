/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:01:04 by fidriss           #+#    #+#             */
/*   Updated: 2024/10/11 14:55:51 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	built_in_execution(t_command *cmd, t_env	**env)
{
	if (!ft_strncmp(cmd->command, "cd", 3))
		cmd->exit_status = ft_cd(cmd, env);
	else if (!ft_strncmp(cmd->command, "echo", 5))
		cmd->exit_status = ft_echo(cmd);
	else if (!ft_strncmp(cmd->command, "pwd", 4))
		cmd->exit_status = ft_pwd(env);
	else if (!ft_strncmp(cmd->command, "export", 7))
		cmd->exit_status = ft_export(cmd, env);
	else if (!ft_strncmp(cmd->command, "unset", 6))
		cmd->exit_status = ft_unset(cmd, env);
	else if (!ft_strncmp(cmd->command, "env", 4))
		cmd->exit_status = ft_env(env);
	else if (!ft_strncmp(cmd->command, "exit", 5))
		ft_exit(cmd);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	else if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	else if (!ft_strncmp(cmd, "export", 7))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	else if (!ft_strncmp(cmd, "env", 4))
		return (1);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	else
		return (0);
}
