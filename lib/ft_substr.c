/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:13:08 by fidriss           #+#    #+#             */
/*   Updated: 2024/08/25 14:35:04 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*str;
	size_t			slen;

	i = 0;
	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (start > slen)
		return (ft_strdup(""));
	if (len + start > slen)
	{
		len = slen - start;
	}
	str = malloc(len + 1);
	if (!str)
		return (0);
	while (s[start] && i < len)
	{
		str[i] = s[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
