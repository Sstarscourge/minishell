/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:19:14 by fidriss           #+#    #+#             */
/*   Updated: 2024/05/09 15:47:00 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	ft_putnbr(long nbr)
{
	int	count;
	int	result;

	count = 0;
	result = 0;
	if (nbr < 0)
	{
		count = ft_putchar('-');
		if (count == -1)
			return (-1); 
		result = ft_putunbr(-nbr);
		if (result == -1)
			return (-1);
		return (count + result);
	}
	else
	{
		count = ft_putunbr(nbr);
		if (count == -1)
			return (-1);
		return (count);
	}
}
