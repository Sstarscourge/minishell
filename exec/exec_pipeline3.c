/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:04:15 by fidriss           #+#    #+#             */
/*   Updated: 2024/10/14 20:49:18 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_pfds(t_command *current, t_pfds *pfds)
{
	if (current->next && current->oa_files == NULL)
	{
		if (pfds->pfd[0] != -1)
			close(pfds->pfd[0]);
		dup2(pfds->pfd[1], STDOUT_FILENO);
		if (pfds->pfd[1] != -1)
			close(pfds->pfd[1]);
	}
	if ((pfds->prev_pfd[0] != -1 || pfds->prev_pfd[1] != 1)
		&& current->heredoc_delimiters == NULL && current->input_files == NULL)
	{
		dup2(pfds->prev_pfd[0], STDIN_FILENO);
		if (pfds->prev_pfd[0] != -1)
			close(pfds->prev_pfd[0]);
	}
	if (pfds->prev_pfd[1] != -1)
		close(pfds->prev_pfd[1]);
	if (pfds->pfd[0] != -1)
		close(pfds->pfd[0]);
	if (pfds->pfd[1] != -1)
		close(pfds->pfd[1]);
	if (pfds->prev_pfd[0] != -1)
		close(pfds->prev_pfd[0]);
}

void	execute_builtin_or_bin(t_command *current, char **envp, t_env *env)
{
	if (current->command[0] == '\0')
	{
		print_error("Command not found", "");
		exit(127);
	}
	if (current->command == NULL)
		exit(0);
	if (is_builtin(current->command))
	{
		built_in_execution(current, &env);
		exit(current->exit_status);
	}
	envp = list_to_pointer(env);
	current->full_path = is_execute(current->command, envp, &env);
	if (current->full_path == NULL)
		check_bin(current, envp);
	if (execve(current->full_path, current->argsp, envp) == -1)
	{
		free(current->full_path);
		free_array(envp);
		exit(1);
	}
}

void	execute_child_process(t_command *current,
		t_pfds *pfds, char **envp, t_env *env)
{
	handle_pfds(current, pfds);
	if (current->input_files)
		handle_input_redirection(current->input_files, 1);
	if (current->oa_files)
		handle_output_redirection(current->oa_files, 1);
	execute_builtin_or_bin(current, envp, env);
}

void	execute_builtin_command(t_command *current, t_env **env, int *exit_stat)
{
	handle_built_in(current, env);
	*exit_stat = current->exit_status;
}
