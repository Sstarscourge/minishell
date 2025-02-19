/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:30:03 by fidriss           #+#    #+#             */
/*   Updated: 2024/10/11 10:45:53 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sighandle(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 2);
	exit(130);
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sighdl(int sig)
{
	(void)sig;
	write (1, "\n", 1);
	exit(1);
}

void	sighdl2(int sig)
{
	(void)sig;
	write (1, "\n", 1);
	g_signal = 24;
	exit(24);
}
