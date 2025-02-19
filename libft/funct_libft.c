/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenchel <abenchel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:21:14 by abenchel          #+#    #+#             */
/*   Updated: 2024/10/05 03:13:42 by abenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(char *s1)
{
	size_t	size;
	char	*s2;

	if (!s1)
		return (0);
	size = ft_strlen(s1);
	s2 = (char *)malloc(size + 1);
	if (!s2)
		return (NULL);
	ft_memcpy(s2, s1, size);
	s2[size] = '\0';
	return (s2);
}

char	**set_free(char **res, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		free(res[j]);
		j++;
	}
	free(res);
	return (NULL);
}

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	size_t	i;
	char	*s1;
	char	*s2;

	s1 = (char *)dst;
	s2 = (char *)src;
	i = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	while (i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	return (dst);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	len_s;
	size_t	len_sub;
	char	*sub;

	i = 0;
	len_s = ft_strlen(s);
	if (!s)
		return (NULL);
	if (len_s < start)
		return (ft_strdup(""));
	len_sub = len_s - start;
	if (len < len_sub)
		len_sub = len;
	sub = (char *)malloc(sizeof(char) * (len_sub + 1));
	if (!sub)
		return (NULL);
	while (i < len_sub)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}
