/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 12:47:36 by fidriss           #+#    #+#             */
/*   Updated: 2024/05/09 15:47:16 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dest;
	char	*sc;

	dest = (char *)dst;
	sc = (char *)src;
	if (!dest && !sc)
	{
		return (0);
	}
	if (dest > sc)
	{
		while (len > 0)
		{
			dest[len - 1] = sc[len - 1];
			len--;
		}
		return (dest);
	}
	else
	{
		return (ft_memcpy(dst, src, len));
	}
}
