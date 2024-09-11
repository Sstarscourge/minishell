/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:14:01 by fidriss           #+#    #+#             */
/*   Updated: 2024/05/09 15:47:00 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	print_content(const char *specifier, va_list ap)
{
	int	count;

	count = 0;
	if (!specifier || !*specifier)
		return (-1);
	if (*specifier == 'c')
		count += ft_putchar(va_arg(ap, int));
	else if (*specifier == 's')
		count += ft_putstr(va_arg(ap, char *));
	else if (*specifier == 'd')
		count += ft_putnbr((long)va_arg(ap, int));
	else if (*specifier == 'i')
		count += ft_putnbr((long)va_arg(ap, int));
	else if (*specifier == 'u')
		count += ft_putunbr((unsigned int)va_arg(ap, int));
	else if (*specifier == 'p')
		count += ft_putaddress(va_arg(ap, unsigned long), "0123456789abcdef");
	else if (*specifier == 'x')
		count += ft_puthexa(va_arg(ap, unsigned int), "0123456789abcdef");
	else if (*specifier == 'X')
		count += ft_puthexa(va_arg(ap, unsigned int), "0123456789ABCDEF");
	else
		count += write (1, specifier, 1);
	return (count);
}

int	ft_check(const char	*str, va_list	ap)
{
	int	count;
	int	result;

	result = 0;
	count = 0;
	while (*str)
	{
		if (*str == '%')
		{
			result = print_content(++str, ap);
			if (result == -1)
				return (-1);
			count += result;
		}
		else
		{
			result = write (1, str, 1);
			if (result == -1)
				return (-1);
			count += result;
		}
		str++;
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	ap;

	count = 0;
	if (!str)
		return (-1);
	va_start(ap, str);
	count = ft_check(str, ap);
	if (count == -1)
		return (-1);
	va_end(ap);
	return (count);
}
