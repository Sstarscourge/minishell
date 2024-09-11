/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 12:49:03 by fidriss           #+#    #+#             */
/*   Updated: 2024/05/09 15:45:03 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

char	*ft_strdup_gnl(char *s1)
{
	int		i;
	char	*s2;

	i = 0;
	if (!s1)
		return (0);
	s2 = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!s2)
		return (0);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		k;
	int		j;
	char	*ret;

	if (s1 == NULL && s2 == NULL)
		return (0);
	i = 0;
	k = 0;
	j = 0;
	ret = malloc(ft_strlen(s1) + ft_strlen(s2) + 1 * sizeof(char));
	if (!ret)
		return (0);
	while (s1 && s1[k] != '\0')
		ret[i++] = s1[k++];
	while (s2 && s2[j] != '\0')
		ret[i++] = s2[j++];
	ret[i] = '\0';
	free(s1);
	return (ret);
}

char	*ft_substr_gnl(char *s, int start, int end, int indicator)
{
	int		i;
	char	*str;

	i = 0;
	if (!s || !s[start])
		str = 0;
	else
	{
		str = malloc(end - start + 2);
		if (!str)
			return (0);
		while (s[start] && start <= end)
		{
			str[i] = s[start];
			start++;
			i++;
		}
		str[i] = '\0';
	}
	if (indicator)
		free(s);
	return (str);
}

int	ft_strchr_gnl(char *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == (char)c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}
