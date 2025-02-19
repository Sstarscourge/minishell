/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 22:27:46 by fidriss           #+#    #+#             */
/*   Updated: 2024/10/05 22:28:06 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*after_equal_sign(char *string)
{
	int		i;
	char	*value;

	i = 0;
	while (string[i] && string[i] != '=')
		i++;
	if (string[i] == '\0')
		return (NULL);
	if (string[i + 1] == '\0')
		return (ft_strdup(""));
	value = ft_substr(string, i + 1, ft_strlen(string) - (i + 1));
	return (value);
}

char	*before_equal_sign(char *string)
{
	int		i;
	char	*name;

	i = 0;
	while (string[i] && string[i] != '=')
		i++;
	if (string[i] == '=' && i == 0)
		return (NULL);
	name = ft_substr(string, 0, i);
	return (name);
}
