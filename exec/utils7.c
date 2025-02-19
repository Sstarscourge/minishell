/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:23:09 by fidriss           #+#    #+#             */
/*   Updated: 2024/10/06 11:30:11 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	skip_delimiters(char *s, char del)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] == del)
		i++;
	return (i);
}

size_t	handle_quotes(char *s, char del)
{
	size_t	i;

	i = 0;
	if (s[i] && s[i] == '"')
		i += skip_quote((char *)&s[i], '"');
	else if (s[i] && s[i] == '\'')
		i += skip_quote((char *)&s[i], '\'');
	else
	{
		while (s[i] && (s[i] != del))
			i++;
	}
	return (i);
}

size_t	count_words(char *s, char del)
{
	size_t	i;
	size_t	word;

	i = 0;
	word = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		i += skip_delimiters(&s[i], del);
		if (s[i] && (s[i] != del))
		{
			word++;
			i += handle_quotes(&s[i], del);
		}
	}
	return (word);
}

char	**allocate_args(t_list *arg_list)
{
	int		len;
	char	**args;

	len = ft_lstsize(arg_list);
	args = malloc(sizeof(char *) * (len + 1));
	if (!args)
	{
		ft_lstclear_list(&arg_list);
		return (NULL);
	}
	return (args);
}

void	free_args(char **args, int i)
{
	while (i > 0)
		free(args[--i]);
	free(args);
}
