/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct_libft5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenchel <abenchel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 03:01:07 by abenchel          #+#    #+#             */
/*   Updated: 2024/10/05 03:01:21 by abenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2, int flag)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*concat;

	if (!s1 && !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	concat = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!concat)
		return (NULL);
	if (s1)
		ft_memcpy(concat, s1, len_s1);
	ft_memcpy(concat + len_s1, s2, len_s2);
	concat[len_s1 + len_s2] = '\0';
	if (flag == 1)
		free(s1);
	if (flag == 2)
	{
		free(s1);
		free(s2);
	}
	return (concat);
}

static int	check(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t	first;
	size_t	last;
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	first = 0;
	last = ft_strlen(s1);
	while (check(set, s1[first]))
		first++;
	if (first == last)
	{
		trimmed = ft_strdup("");
		free(s1);
		return (trimmed);
	}
	while (check(set, s1[last - 1]))
		last--;
	trimmed = ft_substr(s1, first, last - first);
	free(s1);
	return (trimmed);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1 && s2 && (s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}
