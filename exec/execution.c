/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:42:52 by fidriss           #+#    #+#             */
/*   Updated: 2024/10/14 21:31:46 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_built_in(t_command *current, t_env **env)
{
	int			original_stdout;
	int			original_stdin;

	original_stdout = dup(STDOUT_FILENO);
	original_stdin = dup(STDIN_FILENO);
	if (current->heredoc_delimiters)
		handle_heredoc_redirections(current, *env, 0);
	if (current->input_files)
		handle_input_redirection(current->input_files, 0);
	if (current->oa_files)
		handle_output_redirection(current->oa_files, 0);
	built_in_execution(current, env);
	dup2(original_stdout, STDOUT_FILENO);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdout);
	close(original_stdin);
}

void	exec_child_process(t_command *current, t_env **env, char **envp)
{
	signal(SIGQUIT, SIG_DFL);
	if (current->heredoc_delimiters)
		handle_heredoc_redirections(current, *env, 0);
	signal (SIGINT, sighandle);
	if (current->input_files)
		handle_input_redirection(current->input_files, 1);
	if (current->oa_files)
		handle_output_redirection(current->oa_files, 1);
	if (current->command == NULL)
		exit(current->exit_status);
	if (current->command[0] == '\0')
	{
		print_error("Command not found", "");
		exit(127);
	}
	envp = list_to_pointer(*env);
	current->full_path = is_execute(current->command, envp, env);
	if (current->full_path == NULL)
		check_bin(current, envp);
	if (execve(current->full_path, current->argsp, envp) == -1)
	{
		free(current->full_path);
		free_array(envp);
		exit(1);
	}
}

void	execute_command(t_command *cmd, char **envp,
			t_env **env, int *exit_stat)
{
	int			pid;
	t_command	*current;
	int			signum;

	current = cmd;
	if (is_builtin(current->command))
		execute_builtin_command(current, env, exit_stat);
	else
	{
		pid = fork();
		if (pid == 0)
			exec_child_process(current, env, envp);
		else
		{
			waitpid(pid, exit_stat, 0);
			if (WIFEXITED(*exit_stat))
				*exit_stat = WEXITSTATUS(*exit_stat);
			else if (WIFSIGNALED(*exit_stat))
			{
				signum = WTERMSIG(*exit_stat);
				handle_signal_exit_status(signum, exit_stat);
			}
		}
	}
	ft_clear_command(&cmd);
}

void	ft_execute(t_command *cmd, char **envp, t_env **env, int *exit_status)
{
	if (!cmd)
		return ;
	if (!cmd->pipe_out)
	{
		execute_command(cmd, envp, env, exit_status);
	}
	else
		execute_pipeline(cmd, envp, env, exit_status);
}
