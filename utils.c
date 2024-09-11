/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:28:19 by fidriss           #+#    #+#             */
/*   Updated: 2024/09/08 10:08:02 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*list_to_pointer(t_env *env)
{
	char	*tab;
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	tab = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env)
	{
		tab[i] = ft_strjoin(env->name, "=");
		tab[i] = ft_strjoin(tab[i], env->value);
		i++;
		env = env->next;
	}
	tab[i] = NULL;
	return (tab);
}
