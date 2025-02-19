/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct_libft3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:53:31 by abenchel          #+#    #+#             */
/*   Updated: 2024/10/08 22:05:53 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	checksign(const char *str, int i, int sign)
{
	if (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign *= -1;
	}
	return (sign);
}

long long	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	result;
	long long	tmp;

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

static int	countdeg(int n)
{
	int	num_deg;

	if (n <= 0)
		num_deg = 1;
	else if (n != 0)
		num_deg = 0;
	while (n != 0)
	{
		n /= 10;
		num_deg++;
	}
	return (num_deg);
}

static int	is_neg(int n)
{
	int	signe;

	signe = 1;
	if (n < 0)
		signe = -1;
	return (signe);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		num_deg;
	int		signe;

	signe = is_neg(n);
	num_deg = countdeg(n);
	str = (char *)malloc((num_deg + 1) * sizeof(char));
	if (!str)
		return (0);
	if (n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
	}
	if (n < 0)
		str[0] = '-';
	i = num_deg - 1;
	while (n != 0)
	{
		str[i--] = '0' + (n % 10) * signe;
		n /= 10;
	}
	str[num_deg] = '\0';
	return (str);
}
