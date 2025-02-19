/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 22:07:51 by fidriss           #+#    #+#             */
/*   Updated: 2024/10/14 17:47:45 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_child_process(t_command *current,
			t_pfds *pfds, char **envp, t_env **env)
{
	signal (SIGINT, sighandle);
	signal(SIGQUIT, SIG_DFL);
	execute_child_process(current, pfds, envp, *env);
}

void	handle_signal_exit_status(int signum, int *exit_status)
{
	if (signum == 3 || signum == 2)
	{
		*exit_status = 128 + WTERMSIG(*exit_status);
		if (*exit_status == 129)
			*exit_status = 1;
		if (*exit_status == 131)
			ft_putstr_fd("Quit: 3\n", 2);
	}
}

void	wait_for_processes(int	*pids, int count, int *exit_status)
{
	int	i;
	int	signum;
	int	tmp;

	i = 0;
	tmp = *exit_status;
	while ((waitpid(pids[i], exit_status, 0) != -1) && i <= count)
	{
		if (WIFEXITED(*exit_status))
			*exit_status = WEXITSTATUS(*exit_status);
		else if (WIFSIGNALED(*exit_status))
		{
			signum = WTERMSIG(*exit_status);
			handle_signal_exit_status(signum, exit_status);
		}
		i++;
	}
	if (tmp == 1)
		*exit_status = 1;
}
