/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenchel <abenchel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 03:46:33 by abenchel          #+#    #+#             */
/*   Updated: 2024/10/06 20:58:47 by abenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	finddollar(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '$')
		i++;
	free(str);
	str = NULL;
	return (i);
}

char	*beforedollar(char *s)
{
	int		i;
	char	*new;

	i = 0;
	new = malloc(finddollar(s) + 1);
	while (i < finddollar(s))
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	free(s);
	return (new);
}

char	*ft_strreplace(char *str, char *find, char *replace)
{
	char	*new_str;
	size_t	str_len;
	size_t	i;

	str_len = ft_strlen(str);
	new_str = malloc(str_len + ft_strlen(replace) - ft_strlen(find));
	i = 0;
	while (i < str_len)
	{
		if (ft_strncmp(str + i, find, ft_strlen(find)) == 0)
		{
			ft_strncpy(new_str + i, replace, ft_strlen(replace));
			i += ft_strlen(replace);
		}
		else
		{
			new_str[i] = str[i];
			i++;
		}
	}
	new_str[i] = '\0';
	return (new_str);
}

int	count_pipe(t_elem *el)
{
	int		count;
	t_elem	*tmp;

	tmp = el;
	count = 0;
	while (tmp)
	{
		if (tmp->type == PIPE_LINE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}
