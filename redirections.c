/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 09:39:44 by fidriss           #+#    #+#             */
/*   Updated: 2024/09/09 12:52:14 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	void	handle_input_redirection(t_list *input_file)
	{
		int	fd;

		fd = -1;
		while (input_file)
		{
			if (fd != -1)
				close(fd);
			fd = open(input_file->content, O_RDONLY);
			if (fd == -1)
			{
				perror("open");
				exit(1);
			}
			input_file = input_file->next;
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
	}
