/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:08:00 by fidriss           #+#    #+#             */
/*   Updated: 2024/08/24 16:22:58 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_command *cmd)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	i = 1;
	j = 0;
	if (cmd->arg_count == 1)
	{
		printf("\n");
		return ;
	}
	if (cmd->args[i][0] == '-' && cmd->args[i][1] == 'n')
	{
		while (cmd->args[i][j] == 'n')
			j++;
		if (cmd->args[i][j] == '\0')
		{
			flag = 1;
			i++;
		}
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
}
