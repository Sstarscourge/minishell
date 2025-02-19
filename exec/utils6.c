/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 01:57:03 by abenchel          #+#    #+#             */
/*   Updated: 2024/10/06 11:40:17 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

size_t	wordlen(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

void	write_error(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(1, "error :", 7);
	write(1, str, len);
	write(1, "\n", 1);
	return ;
}

void	fill_args(t_command *cmd)
{
	while (cmd)
	{
		cmd->argsp = list_to_char(cmd->args);
		cmd = cmd->next;
	}
}
