/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:53:37 by fidriss           #+#    #+#             */
/*   Updated: 2024/10/14 22:16:52 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_in_file(char *line, int fd)
{
	ft_putstr_fd(line, fd);
	write(fd, "\n", 1);
}

void	process_heredoc_line(t_command *cmd, int fd, t_env *env)
{
	char	*line;

	line = readline(">");
	while (line && ft_strncmp(line, cmd->heredoc_delimiters->content,
			ft_strlen(cmd->heredoc_delimiters->content) + 1))
	{
		if (cmd->heredoc_delimiters->next == NULL && line)
		{
			if (cmd->heredoc_delimiters->state == 2)
				line = expand_line(line, env, cmd);
			write_in_file(line, fd);
		}
		add_history(line);
		if (line)
		{
			free(line);
			line = NULL;
		}
		line = readline(">");
	}
	if (line)
		free(line);
}

void	handle_heredoc_process(t_command *cmd, t_env *env)
{
	int		fd;
	t_list	*tmp;

	tmp = cmd->heredoc_delimiters;
	while (cmd->heredoc_delimiters)
	{
		unlink("/tmp/heredoc.txt");
		fd = open("/tmp/heredoc.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
		process_heredoc_line(cmd, fd, env);
		close(fd);
		cmd->heredoc_delimiters = cmd->heredoc_delimiters->next;
	}
	ft_lstclear_list(&tmp);
	cmd->heredoc_delimiters = NULL;
}

void	handle_heredoc(t_command *cmd, t_env *env, int flag)
{
	int	pid;

	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		if (flag == 0)
			signal (SIGINT, sighdl);
		else
			signal(SIGINT, sighdl2);
		handle_heredoc_process(cmd, env);
		exit(cmd->exit_status);
	}
	else
	{
		waitpid(pid, &cmd->exit_status, 0);
		if (WIFEXITED(cmd->exit_status))
			cmd->exit_status = WEXITSTATUS(cmd->exit_status);
		if (WIFSIGNALED(cmd->exit_status) && flag == 0)
			cmd->exit_status = 1;
		if (WIFSIGNALED(cmd->exit_status) && flag == 1)
			g_signal = 24;
	}
}

void	handle_heredoc_redirections(t_command *cmd, t_env *env, int flag)
{
	int	fd;

	if (!cmd->heredoc_delimiters)
		return ;
	handle_heredoc(cmd, env, flag);
	if (g_signal == 24)
		return ;
	if (cmd->exit_status == 1 && flag == 0)
		exit (1);
	fd = open("/tmp/heredoc.txt", O_RDONLY);
	if (fd != -1)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
		close(fd);
	}
}
