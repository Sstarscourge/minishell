/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 10:54:29 by fidriss           #+#    #+#             */
/*   Updated: 2024/09/10 15:34:55 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	if (!content)
		return (0);
	node = malloc(sizeof(t_list));
	if (!node)
	{
		return (0);
	}
	node->content = content;
	node->next = 0;
	return (node);
}
