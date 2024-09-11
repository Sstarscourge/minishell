/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 11:58:07 by fidriss           #+#    #+#             */
/*   Updated: 2024/05/09 15:47:16 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dest;
	char	*sc;
	size_t	i;

	dest = (char *)dst;
	sc = (char *)src;
	i = 0;
	if (!dest && !sc)
	{
		return (0);
	}
	while (i < n)
	{
		dest[i] = sc[i];
		i++;
	}
	return (dest);
}
