/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:12:13 by fidriss           #+#    #+#             */
/*   Updated: 2024/09/04 09:21:02 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

char	*ft_strmapi(char *s, char (*f)(unsigned	int, char))
{
	char			*str;
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return (0);
	str = ft_strdup(s);
	if (!str)
	{
		return (0);
	}
	while (str[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	return (str);
}
