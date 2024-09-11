/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 09:56:21 by fidriss           #+#    #+#             */
/*   Updated: 2024/05/09 15:47:16 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*sotc;
	t_list	*urbannightmare;
	void	*newcontenttofreeifmallocfails;

	if (!lst || !f || !del)
	{
		return (0);
	}
	sotc = 0;
	while (lst)
	{
		newcontenttofreeifmallocfails = f(lst->content);
		urbannightmare = ft_lstnew(newcontenttofreeifmallocfails);
		if (!urbannightmare)
		{
			del(newcontenttofreeifmallocfails);
			ft_lstclear(&sotc, del);
			return (0);
		}
		ft_lstadd_back(&sotc, urbannightmare);
		lst = lst->next;
	}
	return (sotc);
}
