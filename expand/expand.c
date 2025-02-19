/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:22:01 by abenchel          #+#    #+#             */
/*   Updated: 2024/10/14 16:40:16 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_d(char **str, t_env *envp, int *i, int *exit_status)
{
	char	*new_str;

	if (**str == '\0')
		return (ft_strdup("$"));
	else if (**str == '$')
	{
		new_str = ft_strdup("");
		(*str)++;
	}
	else if (**str == '?')
	{
		new_str = ft_itoa(*exit_status);
		(*str)++;
	}
	else
		return (env_string(beforedolaar(*str, i), envp));
	return (new_str);
}

char	*place(t_elem *elem, t_env *envp, int *exit_status)
{
	t_utile	utl;

	utl.returnstr = ft_strdup("");
	utl.str = elem->content;
	while (*utl.str)
	{
		utl.i = 0;
		if (*utl.str == '$')
		{
			utl.str++;
			utl.new_str = handle_d(&utl.str, envp, &utl.i, exit_status);
		}
		else if (ft_isalpha(*utl.str))
			utl.new_str = beforedolaar(utl.str, &utl.i);
		else
		{
			utl.new_str = makestring(*utl.str);
			utl.str++;
		}
		utl.returnstr = ft_strjoin(utl.returnstr, utl.new_str, 2);
		utl.str += utl.i;
	}
	free(elem->content);
	return (utl.returnstr);
}

t_elem	*utile_expand(t_elem *el)
{
	el = el->next;
	while (el != NULL && el->type == WHITE_SPACE)
		el = el->next;
	while (el != NULL && el->type == WORD)
		el = el->next;
	while (el != NULL && el->type == WHITE_SPACE)
		el = el->next;
	return (el);
}

void	expand(t_elem *elem, t_env *env, int exit_status)
{
	t_elem	*el;
	t_env	*envp;

	if (!elem)
		return ;
	el = elem;
	while (el)
	{
		envp = env;
		while (el && el->state == IN_QUOTE)
			el = el->next;
		while (el != NULL && (el->type == HERE_DOC))
			el = utile_expand(el);
		if (!el)
			return ;
		if (el->type == WORD && ft_strchrr(el->content, '$'))
			el->content = place(el, envp, &exit_status);
		el = el->next;
	}
}
