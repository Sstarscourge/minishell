/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:42:58 by fidriss           #+#    #+#             */
/*   Updated: 2024/05/09 15:47:00 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	ft_putaddress(unsigned long nbr, char	*base)
{
	int	count;
	int	result;

	count = 0;
	result = 0;
	if (nbr < 16)
	{
		count = ft_putstr("0x");
		if (count == -1)
			return (-1);
		result = ft_putchar(base[nbr]);
		if (result == -1)
			return (-1);
		return (count + result);
	}
	else
	{
		count = ft_putaddress((nbr / 16), base);
		if (count == -1)
			return (-1);
		result = ft_putchar(base[nbr % 16]);
		if (result == -1)
			return (-1);
		return (count + result);
	}
}
