/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:53:37 by fidriss           #+#    #+#             */
/*   Updated: 2024/09/13 12:48:39 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_in_file(char *line)
{
	int	fd;

	fd = open("/tmp/heredoc.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	ft_putstr_fd(line, fd);
	write(fd, "\n", 1);
	close(fd);
}

void	handle_heredoc(t_command *cmd)
{
	char	*line;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		while (cmd->heredoc_delimiters)
		{
			unlink("/tmp/heredoc.txt");
			line = readline(">");
			while (ft_strncmp(line, cmd->heredoc_delimiters->content, 
					ft_strlen(cmd->heredoc_delimiters->content) + 1))
			{
				if (cmd->heredoc_delimiters->next == NULL)
					write_in_file(line);
				add_history(line);
				free(line);
				line = readline(">");
			}
			if (!line)
				break ;
			free(line);
			cmd->heredoc_delimiters = cmd->heredoc_delimiters->next;
		}
		exit(0);
	}
	else
		wait(NULL);
}

void	handle_heredoc_redirections(t_command *cmd)
{
	int	fd;

	handle_heredoc(cmd);
	fd = open("/tmp/heredoc.txt", O_RDONLY);
	if (fd == -1)
	{
		exit(0);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(fd);
}
