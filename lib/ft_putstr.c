/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:18:48 by fidriss           #+#    #+#             */
/*   Updated: 2024/05/09 15:47:00 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	ft_putstr(char	*str)
{
	int	count;
	int	result;
	int	i;

	count = 0;
	result = 0;
	i = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (str[i])
	{
		result = ft_putchar(str[i]);
		if (result == -1)
			return (-1);
		count += result;
		i++;
	}
	return (count);
}
