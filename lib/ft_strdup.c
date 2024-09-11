/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:40:50 by fidriss           #+#    #+#             */
/*   Updated: 2024/09/10 15:30:51 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

char	*ft_strdup(char *s1)
{
	int		i;
	char	*s2;

	i = 0;
	if (!s1)
		return (0);
	s2 = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!s2)
	{
		return (0);
	}
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
