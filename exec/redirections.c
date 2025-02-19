/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 09:39:44 by fidriss           #+#    #+#             */
/*   Updated: 2024/10/07 02:10:01 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_input_redirection(t_list *input_file, int flag)
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
			if (flag == 0)
				return (1);
			exit (1);
		}
		input_file = input_file->next;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(fd);
	return (0);
}

void	dup_output(int fd)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(fd);
}

int	handle_output_redirection(t_list *output_files, int flag)
{
	int	fd;

	fd = -1;
	while (output_files)
	{
		if (fd != -1)
			close(fd);
		if (output_files->type == 1)
			fd = open(output_files->content, O_WRONLY
					| O_CREAT | O_TRUNC, 0644);
		else
			fd = open(output_files->content, O_WRONLY
					| O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("open");
			if (flag == 0)
				return (1);
			exit(1);
		}
		output_files = output_files->next;
	}
	dup_output(fd);
	return (0);
}
