/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:02:30 by fidriss           #+#    #+#             */
/*   Updated: 2024/05/09 15:47:16 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static	int	count_len(long nb)
{
	int	len;

	len = 1;
	while (nb >= 10)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

static	char	*ft_put(char *str, long nb, int nb_len, int sign)
{
	str[nb_len--] = 0;
	if (nb == 0)
	{
		str[nb_len] = '0'; 
	}
	while (nb)
	{
		str[nb_len--] = nb % 10 + '0';
		nb /= 10;
	}
	if (sign == -1)
	{
		str[nb_len] = '-';
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		nb_len;
	long	nb;
	int		sign;
	char	*str;

	nb = n;
	sign = 1;
	if (nb < 0)
	{
		sign = -1;
		nb *= -1;
		nb_len = count_len(nb) + 1;
	}
	else
		nb_len = count_len(nb);
	str = malloc ((nb_len + 1) * sizeof(char));
	if (!str)
	{
		return (0);
	}
	return (ft_put(str, nb, nb_len, sign));
}
