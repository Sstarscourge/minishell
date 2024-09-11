/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:53:37 by fidriss           #+#    #+#             */
/*   Updated: 2024/09/10 14:54:38 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(t_command *cmd)
{
	char	*line;
	int		fd;
	int		pid;

	while (cmd->heredoc_delimiters)
	{
		pid = fork();
		if (pid == 0)
		{
			while (!ft_strncmp(line, cmd->heredoc_delimiters->content, 
					ft_strlen(cmd->heredoc_delimiters->content)))
			{
				line = readline(">");
				add_history(line);
				if (cmd->heredoc_content == NULL)
				{
					cmd->heredoc_content = ft_lstnew(line);
				}
				else
				{
					ft_lstadd_back(&cmd->heredoc_content, ft_lstnew(line));
				}
			}
			exit(0);
		}
		waitpid(pid, NULL, 0);
		if (cmd->heredoc_delimiters->next)
			cmd->heredoc_delimiters = cmd->heredoc_delimiters->next;
	}
}