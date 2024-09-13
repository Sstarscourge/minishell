/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:28:19 by fidriss           #+#    #+#             */
/*   Updated: 2024/09/13 10:42:05 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_pointer(t_env *env)
{
	char	**tab;
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

t_env	*env_fill(char **envp)
{
	t_env	*env;
	t_env	*tmp;
	int		i;

	if (!envp)
		return (NULL);
	i = 0;
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	tmp = env;
	while (envp[i])
	{
		tmp->name = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
		tmp->value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		if (envp[i + 1])
		{
			tmp->next = malloc(sizeof(t_env));
			tmp = tmp->next;
		}
		else
			tmp->next = NULL;
		i++;
	}
	return (env);
}

void	ft_free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
