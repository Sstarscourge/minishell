/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:05:43 by fidriss           #+#    #+#             */
/*   Updated: 2024/05/09 15:47:16 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static	char	*ft_strdup2(const char *s1, char c)
{
	int		i;
	char	*s2;

	i = 0;
	while (s1[i] && s1[i] != c)
	{
		i++;
	}
	s2 = ft_calloc(i + 1, sizeof(char));
	i = 0;
	if (!s2)
	{
		return (0);
	}
	while (s1[i] && s1[i] != c)
	{
		s2[i] = s1[i];
		i++;
	}
	return (s2);
}

static	int	ft_countwords(char c, char const	*s)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
		{
			i++;
		}
		if (s[i])
		{
			count++;
		}
		while (s[i] && s[i] != c)
		{
			i++;
		}
	}
	return (count);
}

static	char	**ft_free(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free (strs);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;
	int		j;

	if (!s)
		return (0);
	strs = ft_calloc((ft_countwords(c, s) + 1), sizeof(char *));
	if (!strs)
		return (0);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			strs[j++] = ft_strdup2(&s[i], c);
		if (s[i] && strs[j - 1] == 0)
			return (ft_free(strs));
		while (s[i] != c && s[i])
			i++;
	}
	return (strs);
}
