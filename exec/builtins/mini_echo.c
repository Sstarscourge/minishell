/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:08:00 by fidriss           #+#    #+#             */
/*   Updated: 2024/10/03 17:44:05 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_flag(t_command *cmd, int *i)
{
	int	j;
	int	flag;

	flag = 0;
	j = 1;
	while (cmd->argsp[*i] && cmd->argsp[*i][0] == '-'
			&& cmd->argsp[*i][1] == 'n')
	{
		while (cmd->argsp[*i][j] == 'n')
			j++;
		if (cmd->argsp[*i][j] == '\0')
		{
			flag = 1;
			(*i)++;
		}
		else
			break ;
	}
	return (flag);
}

void	print_args(t_command *cmd, int *i)
{
	while (cmd->argsp[*i])
	{
		printf("%s", cmd->argsp[*i]);
		if (cmd->argsp[*i + 1])
			printf(" ");
		(*i)++;
	}
}

int	ft_echo(t_command *cmd)
{
	int	i;
	int	flag;

	i = 1;
	if (cmd->arg_count == 1)
	{
		printf("\n");
		return (0);
	}
	flag = check_flag(cmd, &i);
	print_args(cmd, &i);
	if (!flag)
		printf("\n");
	return (0);
}
