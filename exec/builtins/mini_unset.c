/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:41:59 by abenchel          #+#    #+#             */
/*   Updated: 2024/10/08 21:53:45 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*find_node(t_env *env, char *name)
{
	t_env	*tmp;

	if (!env)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name, ft_strlen(name) + 1) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	delete_node(t_env *env_tmp, t_env **env)
{
	t_env	*tmp_prev;

	if (env_tmp == *env)
	{
		*env = env_tmp->next;
	}
	else
	{
		tmp_prev = *env;
		while (tmp_prev && tmp_prev->next != env_tmp)
			tmp_prev = tmp_prev->next;
		if (tmp_prev)
			tmp_prev->next = env_tmp->next;
	}
	free(env_tmp->name);
	free(env_tmp->value);
	free(env_tmp);
}

int	ft_unset(t_command *cmd, t_env **env)
{
	t_env	*env_tmp;
	int		i;

	i = 1;
	while (cmd->argsp[i])
	{
		if (check_special_characters(cmd->argsp[i]) == 1)
		{
			print_error("not a valid identifier", cmd->argsp[i]);
			return (1);
		}
		env_tmp = *env;
		while (env_tmp)
		{
			if (ft_strncmp(env_tmp->name, cmd->argsp[i],
					ft_strlen(cmd->argsp[i]) + 1) == 0)
			{
				delete_node(env_tmp, env);
				break ;
			}
			env_tmp = env_tmp->next;
		}
		i++;
	}
	return (0);
}
