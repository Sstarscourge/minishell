/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:46:57 by abenchel          #+#    #+#             */
/*   Updated: 2024/10/11 11:10:20 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_space(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] != '\0' && ((line[i] >= 9 && line[i] <= 13)
			|| line[i] == 32))
		i++;
	return (i);
}

char	*check_pipe(char *line, int	*exit_stat)
{
	int	i;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i])
	{
		if (line && line[i] == '|')
		{
			i++;
			i += skip_space(&line[i]);
			if (!line[i] || line[i] == '|')
				line = print_syntax_error(line, exit_stat);
		}
		if (line && (line[i] == '\'' || line[i] == '"'))
			i += skip_quote(&line[i], line[i]);
		if (!line || !line[i])
			return (line);
		i++;
	}
	return (line);
}

char	*check_special(char c, char *line, int	*exit_status)

{
	if (is_special(c) || c == '|')
		line = print_syntax_error(line, exit_status);
	return (line);
}

char	*check_token(char *line, int *exit_stat)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if ((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<' && line[i
					+ 1] == '<'))
		{
			i += 2;
			i += skip_space(&line[i]);
			line = check_special(line[i], line, exit_stat);
		}
		else if (line && is_special(line[i]))
		{
			i++;
			i += skip_space(&line[i]);
			line = check_special(line[i], line, exit_stat);
		}
		if (line && (line[i] == '\'' || line[i] == '"'))
			i += skip_quote(&line[i], line[i]);
		if (!line || !line[i])
			return (line);
		i++;
	}
	return (line);
}

char	*check_error(char *line, int *exit_status)
{
	t_operat	ope;

	ope.dbl_quote = 0;
	ope.sgl_quote = 0;
	if (line && *line == '|')
		line = print_syntax_error(line, exit_status);
	if (line)
	{
		ope = check_quotes(line);
		if (ope.sgl_quote == 1 || ope.dbl_quote == 1)
			line = print_syntax_error(line, exit_status);
		if (line)
			line = check_pipe(line, exit_status);
	}
	if (line)
		line = check_token(line, exit_status);
	return (line);
}
