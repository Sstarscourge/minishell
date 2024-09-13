/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:04:15 by fidriss           #+#    #+#             */
/*   Updated: 2024/09/13 11:07:43 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	built_in_execution(t_command *cmd, t_env	*env)
// {
// 	if (!ft_strncmp(cmd->command, "cd", 3))
// 		ft_cd(cmd, env);
// 	else if (!ft_strncmp(cmd->command, "echo", 5))
// 		ft_echo(cmd);
// 	else if (!ft_strncmp(cmd->command, "pwd", 4))
// 		ft_pwd();
// 	else if (!ft_strncmp(cmd->command, "export", 7))
// 		ft_export(cmd, env);
// 	else if (!ft_strncmp(cmd->command, "unset", 6))
// 		ft_unset(cmd, env);
// 	else if (!ft_strncmp(cmd->command, "env", 4))
// 		ft_env(env);
// 	else if (!ft_strncmp(cmd->command, "exit", 5))
// 		ft_exit(cmd);
// 	else
// 		return (0);
// 	return (1);
// }

void	create_pipe(int pfd[2])
{
	if (pipe(pfd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

void	handle_redirections(t_command *current)
{
	if (current->input_files)
		handle_input_redirection(current->input_files);
	if (current->oa_files)
		handle_output_redirection(current->oa_files);
}

void	close_remaining_pipes(int prev_pfd[2], int pfd[2])
{
	if (prev_pfd[0] != -1)
		close(prev_pfd[0]);
	if (prev_pfd[1] != -1)
		close(prev_pfd[1]);
	close(pfd[0]);
	close(pfd[1]);
}
