/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 12:48:35 by fidriss           #+#    #+#             */
/*   Updated: 2024/05/09 15:45:03 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static int	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*get_leftover(char	*stocking)
{
	int	i;

	i = 0;
	while (stocking && stocking[i] && stocking [i] != '\n')
		i++;
	if (!stocking[i])
		i--;
	return (ft_substr_gnl(stocking, i + 1, ft_strlen_gnl(stocking), 0));
}

char	*get_final_line(char	*stocking)
{
	int	i;

	i = 0;
	while (stocking && stocking[i] && stocking[i] != '\n')
		i++;
	if (!stocking[i])
		i--;
	return (ft_substr_gnl(stocking, 0, i, 1));
}

char	*get_next_line(int fd)
{
	char		*stocking;
	char		buffer[BUFFER_SIZE + 1];
	char		*final_line;
	static char	*leftover;
	int			length;

	length = -1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stocking = ft_strdup_gnl(leftover);
	free(leftover);
	leftover = 0;
	while (ft_strchr_gnl(stocking, '\n') == 0 && length != 0)
	{
		length = read(fd, buffer, BUFFER_SIZE);
		if (length < 0 || (length == 0 && ft_strlen_gnl(stocking) == 0))
			return (free(stocking), NULL);
		buffer[length] = '\0';
		stocking = ft_strjoin_gnl(stocking, buffer);
	}
	leftover = get_leftover(stocking);
	final_line = get_final_line(stocking);
	return (final_line);
}
