/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:42:38 by fidriss           #+#    #+#             */
/*   Updated: 2024/05/09 15:47:00 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	ft_putunbr(unsigned int nb)
{
	long	nbr;
	int		count;
	int		result;

	nbr = nb;
	count = 0;
	result = 0;
	if (nbr > 9)
	{
		count = ft_putunbr(nbr / 10);
		if (count == -1)
			return (-1);
		result = ft_putunbr(nbr % 10);
		if (result == -1)
			return (-1);
		return (count + result);
	}
	else
	{
		count = ft_putchar(nbr + '0');
		if (count == -1)
			return (-1);
		return (count);
	}
}
