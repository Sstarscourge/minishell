/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:47:45 by fidriss           #+#    #+#             */
/*   Updated: 2024/05/09 15:47:16 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static int	checksign(const	char *str, int i, int sign)
{
	if (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign *= -1;
	}
	return (sign);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;
	long	tmp;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	sign = checksign(str, i, sign);
	if (str[i] && (str[i] == '+' || str[i] == '-'))
		i++;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
		return (0);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		tmp = result;
		result = result * 10 + (str[i++] - '0');
		if (result / 10 != tmp && sign == -1)
			return (0);
		if (result / 10 != tmp)
			return (-1);
	}
	return (result * sign);
}
