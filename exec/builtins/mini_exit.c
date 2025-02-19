/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:24:13 by fidriss           #+#    #+#             */
/*   Updated: 2024/10/14 11:47:34 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_with_error(char *command)
{
	printf("exit\n");
	print_error("numeric argument required", command);
	exit (255);
}

void	exit_with_too_many_args(t_command *cmd)
{
	printf("exit\n");
	print_error("too many arguments", cmd->command);
	cmd->exit_status = 1;
}

void	exit_with_valid_args(t_command *cmd)
{
	printf("exit\n");
	exit(ft_atoi(cmd->argsp[1]));
}

void	exit_with_no_args(void)
{
	printf("exit\n");
	exit(0);
}

void	ft_exit(t_command *cmd)
{
	int			i;
	long long	n;

	i = 0;
	if (cmd->argsp[1] == NULL)
		exit_with_no_args();
	if (cmd->argsp[2] != NULL)
	{
		exit_with_too_many_args(cmd);
		return ;
	}
	if (cmd->argsp[1][i] == '\0')
		exit_with_error(cmd->command);
	while (cmd->argsp[1][i])
	{
		if (cmd->argsp[1][0] == '+' || cmd->argsp[1][0] == '-')
			i++;
		if (!ft_isdigit(cmd->argsp[1][i]))
			exit_with_error(cmd->command);
		i++;
	}
	n = ft_atoi(cmd->argsp[1]);
	if (n == -1)
		exit_with_error(cmd->command);
	exit_with_valid_args(cmd);
}
