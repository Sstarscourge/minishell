/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:24:14 by fidriss           #+#    #+#             */
/*   Updated: 2024/05/09 15:47:16 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static	int	ft_search(char c, char const	*set)
{
	int	i;

	i = 0;
	while (set && set[i])
	{
		if (set[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		begin;
	int		end;
	int		i;
	char	*str;

	if (!s1)
		return (0);
	begin = 0;
	while (s1[begin] && ft_search(s1[begin], set) == 1)
		begin++;
	end = ft_strlen(s1);
	while (end > begin && ft_search(s1[end - 1], set) == 1)
		end--;
	str = malloc (end - begin + 1);
	if (!str)
		return (0);
	i = 0;
	while (begin < end)
		str[i++] = s1[begin++];
	str[i] = '\0';
	return (str);
}
