/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_funct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:24:26 by abenchel          #+#    #+#             */
/*   Updated: 2024/10/06 21:07:49 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_elem	*ft_lstnew_elem(char *content)
{
	t_elem	*new_list;

	new_list = malloc(sizeof(t_elem));
	if (!new_list)
		return (NULL);
	new_list->content = ft_strdup(content);
	new_list->next = NULL;
	return (new_list);
}

void	ft_lstadd_back_elem(t_elem **lst, t_elem *new)
{
	t_elem	*last;

	if (!new)
		return ;
	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlast_elem(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

t_elem	*ft_lstlast_elem(t_elem *lst)
{
	t_elem	*elem2;

	elem2 = lst;
	while (elem2)
	{
		if (!elem2->next)
			return (elem2);
		elem2 = elem2->next;
	}
	return (elem2);
}

t_elem	*elem_fill(char **p)
{
	int		i;
	t_elem	*elem;
	t_elem	*elem2;

	elem = NULL;
	elem2 = NULL;
	if (!p)
		return (NULL);
	i = 0;
	while (p[i])
	{
		elem2 = ft_lstnew_elem(p[i]);
		if (!elem)
			elem = elem2;
		else
			ft_lstadd_back_elem(&elem, elem2);
		i++;
	}
	return (elem);
}
