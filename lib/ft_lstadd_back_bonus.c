/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:14:01 by fidriss           #+#    #+#             */
/*   Updated: 2024/09/11 10:05:45 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*tmp;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	tmp = *alst;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}
