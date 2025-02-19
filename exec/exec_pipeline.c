/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:38:50 by fidriss           #+#    #+#             */
/*   Updated: 2024/10/14 22:04:52 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_fork_error(pid_t pid)
{
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	return (0);
}

int	execute_parent_process(t_pfds	*pfds)
{
	if (pfds->prev_pfd[0] != -1)
		close(pfds->prev_pfd[0]);
	if (pfds->prev_pfd[1] != -1)
		close(pfds->prev_pfd[1]);
	pfds->prev_pfd[0] = pfds->pfd[0];
	pfds->prev_pfd[1] = pfds->pfd[1];
	return (0);
}

int	execute_command_pipe(t_pipeline *pipeline, char **envp,
			t_env **env, int *exit_status)
{
	if (pipeline->current->next)
		create_pipe(pipeline->pfds->pfd);
	handle_heredoc_redirections(pipeline->current, *env, 1);
	if (g_signal != 24)
	{
		pipeline->pids[pipeline->i] = fork();
		if (handle_fork_error(pipeline->pids[pipeline->i]) == 1)
			return (1);
		if (pipeline->pids[pipeline->i] == 0)
			handle_child_process(pipeline->current, pipeline->pfds, envp, env);
		else
			execute_parent_process(pipeline->pfds);
		dup2(pipeline->original_stdin, STDIN_FILENO);
		*exit_status = pipeline->current->exit_status;
		ft_clear_command(&(pipeline->current));
	}
	else
	{
		dup2(pipeline->original_stdin, STDIN_FILENO);
		close(pipeline->original_stdin);
		while (pipeline->current)
			ft_clear_command(&(pipeline->current));
		pipeline->current = NULL;
	}
	return (0);
}

void	initalize_pipeline(t_pipeline *pipeline, t_command *cmd)
{
	int	pipe_count;

	pipe_count = ft_lstcmdsize(cmd);
	pipeline->i = 0;
	pipeline->current = cmd;
	pipeline->pids = malloc(sizeof(int) * (pipe_count + 1));
	pipeline->pids[pipe_count] = 0;
	while (pipeline->i < pipe_count)
	{
		pipeline->pids[pipeline->i] = -1;
		pipeline->i++;
	}
	pipeline->i = 0;
}

void	execute_pipeline(t_command *cmd, char **envp,
			t_env **env, int *exit_status)
{
	t_pipeline	pipeline;

	initalize_pipeline(&pipeline, cmd);
	pipeline.original_stdin = dup(STDIN_FILENO);
	pipeline.pfds = initialize_pfd();
	while (pipeline.current)
	{
		if (execute_command_pipe(&pipeline, envp, env, exit_status) == 1 
			|| g_signal == 24)
		{
			*exit_status = 1;
			break ;
		}
		pipeline.i++;
	}
	wait_for_processes(pipeline.pids, pipeline.i, exit_status);
	close_remaining_pipes(&pipeline);
	while (pipeline.current)
		ft_clear_command(&(pipeline.current));
	free(pipeline.pids);
}
