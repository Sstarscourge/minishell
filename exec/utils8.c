/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:24:40 by fidriss           #+#    #+#             */
/*   Updated: 2024/10/12 13:34:51 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char *str, char *command)
{
	ft_putstr_fd("Minishell : ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

char	**copy_list_to_args(t_list *arg_list, char **args)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = arg_list;
	while (tmp)
	{
		args[i] = ft_strdup(tmp->content);
		if (!args[i])
		{
			free_args(args, i);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

char	**list_to_char(t_list *arg_list)
{
	char	**args;

	args = allocate_args(arg_list);
	if (!args)
		return (NULL);
	args = copy_list_to_args(arg_list, args);
	if (!args)
		return (NULL);
	ft_lstclear_list(&arg_list);
	return (args);
}

char	**ft_split(char *s, char c)
{
	char	**spt;
	size_t	word;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	word = count_words(s, c);
	spt = (char **)malloc(sizeof(char *) * (word + 1));
	if (!spt)
		return (NULL);
	while (i < word)
	{
		while (*s != '\0' && *s == c)
			s++;
		spt[i] = ft_substr(s, 0, wordlen((char *)s, c));
		s += wordlen((char *)s, c);
		if (!spt[i])
			return (set_free(spt, i));
		i++;
	}
	spt[i] = NULL;
	return (spt);
}

int	ft_lstcmdsize(t_command *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
