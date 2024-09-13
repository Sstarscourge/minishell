/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:01:04 by fidriss           #+#    #+#             */
/*   Updated: 2024/09/13 11:01:22 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	built_in_execution(t_command *cmd, t_env	*env)
{
	if (!ft_strncmp(cmd->command, "cd", 3))
		ft_cd(cmd, env);
	else if (!ft_strncmp(cmd->command, "echo", 5))
		ft_echo(cmd);
	else if (!ft_strncmp(cmd->command, "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(cmd->command, "export", 7))
		ft_export(cmd, env);
	else if (!ft_strncmp(cmd->command, "unset", 6))
		ft_unset(cmd, env);
	else if (!ft_strncmp(cmd->command, "env", 4))
		ft_env(env);
	else if (!ft_strncmp(cmd->command, "exit", 5))
		ft_exit(cmd);
	else
		return (0);
	return (1);
}
