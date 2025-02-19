/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:40:26 by fidriss           #+#    #+#             */
/*   Updated: 2024/10/10 19:23:40 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_pipe(int pfd[2])
{
	if (pipe(pfd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

void	close_remaining_pipes(t_pipeline *pipeline)
{
	if (pipeline->pfds->prev_pfd[0] != -1)
		close(pipeline->pfds->prev_pfd[0]);
	if (pipeline->pfds->prev_pfd[1] != -1)
		close(pipeline->pfds->prev_pfd[1]);
	if (pipeline->pfds->pfd[0] != -1)
		close(pipeline->pfds->pfd[0]);
	if (pipeline->pfds->pfd[1] != -1)
		close(pipeline->pfds->pfd[1]);
	close(pipeline->original_stdin);
	free(pipeline->pfds);
}

t_pfds	*initialize_pfd(void)
{
	t_pfds	*pfds;

	pfds = malloc(sizeof(t_pfds));
	if (!pfds)
		exit(1);
	pfds->prev_pfd[0] = -1;
	pfds->prev_pfd[1] = -1;
	pfds->pfd[0] = -1;
	pfds->pfd[1] = -1;
	return (pfds);
}
