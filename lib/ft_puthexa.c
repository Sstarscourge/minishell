/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 20:03:25 by fidriss           #+#    #+#             */
/*   Updated: 2024/05/09 15:47:00 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	ft_puthexa(unsigned int nbr, char	*base)
{
	int	count;
	int	result;

	count = 0;
	result = 0;
	if (nbr < 16)
	{
		result = ft_putchar(base[nbr]);
		if (result == -1)
			return (-1);
		return (result);
	}
	else
	{
		count = ft_puthexa((nbr / 16), base);
		if (count == -1)
			return (-1);
		result = ft_putchar(base[nbr % 16]);
		if (result == -1)
			return (-1);
		return (count + result);
	}
}
