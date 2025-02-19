/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:17:26 by fidriss           #+#    #+#             */
/*   Updated: 2024/10/06 21:10:44 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_env(t_env **env, t_env *node)
{
	t_env	*tmp;

	if (!node)
		return ;
	if (!*env)
	{
		*env = node;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

int	check_existing_node(t_env *env, char *arg)
{
	t_env	*tmp;
	char	*name;

	if (!env)
		return (0);
	name = before_equal_sign(arg);
	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name, ft_strlen(name) + 1) == 0)
		{
			free(name);
			return (1);
		}
		tmp = tmp->next;
	}
	free(name);
	return (0);
}

void	print_export(t_env *env)
{
	if (!env)
		return ;
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->name, env->value);
		else
			printf("declare -x %s\n", env->name);
		env = env->next;
	}
}

t_env	*create_new_node(char *arg)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = before_equal_sign(arg);
	node->value = after_equal_sign(arg);
	node->next = NULL;
	return (node);
}

t_list	*eenv_fill(char **envp)
{
	t_list	*env;
	t_list	*new;
	int		i;

	if (!envp)
		return (NULL);
	i = 0;
	env = NULL;
	while (envp[i])
	{
		new = ft_lstnew(envp[i]);
		if (!env)
			env = new;
		else
			ft_lstadd_back(&env, new);
		i++;
	}
	return (env);
}
