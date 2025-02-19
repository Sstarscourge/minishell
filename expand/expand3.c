/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenchel <abenchel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 03:47:36 by abenchel          #+#    #+#             */
/*   Updated: 2024/10/08 08:56:44 by abenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	for_expand(char *str, int i)
{
	return (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_');
}

char	*beforedolaar(char *str, int *j)
{
	char	*before;
	int		i;

	i = 0;
	while (str[i] && (str[i] != '$') && for_expand(str, i))
	{
		if (str[i] == ' ')
			break ;
		i++;
	}
	before = malloc((i) + 1);
	if (!before)
		return (NULL);
	ft_strncpy(before, str, (i));
	*j += i;
	return (before);
}

void	ft_lstclear_envp(t_env **env)
{
	t_env	*current;

	while (*env)
	{
		current = *env;
		*env = (*env)->next;
		free(current->name);
		free(current->value);
		free(current);
	}
}

char	*env_string(char *str, t_env *env)
{
	char	*new_str;
	t_env	*init;

	init = env;
	new_str = NULL;
	while (init)
	{
		if (!ft_strcmp(str, init->name))
		{
			new_str = ft_strdup(init->value);
			break ;
		}
		init = init->next;
	}
	free(str);
	return (new_str);
}

char	*makestring(char c)
{
	char	*str;

	str = malloc(2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}
