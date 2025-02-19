/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct_libft2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenchel <abenchel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:07:37 by abenchel          #+#    #+#             */
/*   Updated: 2024/10/06 21:35:08 by abenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstclear_list(t_list **head)
{
	t_list	*current;

	while (*head)
	{
		current = *head;
		*head = (*head)->next;
		free(current->content);
		free(current);
	}
	if (!(*head))
		free(*head);
}

void	ft_lstclear_elem(t_elem **head)
{
	t_elem	*current;

	while (*head)
	{
		current = *head;
		*head = (*head)->next;
		free(current->content);
		free(current);
	}
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new_list;

	new_list = malloc(sizeof(t_list));
	if (!new_list)
		return (NULL);
	new_list->content = ft_strdup(content);
	new_list->next = NULL;
	return (new_list);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!new)
		return ;
	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlast(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}
