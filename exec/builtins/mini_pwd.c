/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:53:02 by fidriss           #+#    #+#             */
/*   Updated: 2024/10/07 16:12:21 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_env **env)
{
	t_env	*tmp;

	if (!env || !*env)
		return (1);
	tmp = find_node(*env, "PWD");
	if (!tmp)
		return (1);
	printf("%s\n", tmp->value);
	return (0);
}
