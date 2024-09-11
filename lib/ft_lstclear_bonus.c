/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 17:10:46 by fidriss           #+#    #+#             */
/*   Updated: 2024/05/09 15:47:16 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*bruh;

	if (!lst || !*lst || !del)
	{
		return ;
	}
	bruh = *lst;
	while (bruh)
	{
		tmp = bruh->next;
		ft_lstdelone(bruh, del);
		bruh = tmp;
	}
	*lst = 0;
}
