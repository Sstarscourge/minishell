/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 02:31:54 by abenchel          #+#    #+#             */
/*   Updated: 2024/10/11 11:08:55 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_special(char c)
{
	if (c == '>' || c == '<' || c == '&' || c == '\0')
		return (1);
	return (0);
}

int	skip_quote(char *line, char quote_type)
{
	int	i;

	i = 1;
	if (!line)
		return (0);
	while (line && line[i] && line[i] != quote_type)
		i++;
	if (line[i] == quote_type)
		i++;
	return (i);
}

char	*print_syntax_error(char *line, int *exit_status)

{
	printf("minishell: syntax error\n");
	*exit_status = 258;
	free(line);
	line = NULL;
	return (line);
}

int	checking_quotes(int *op, char *line, int i, char quote)
{
	*op = 1;
	i++;
	while (line[i] && line[i] != quote)
		i++;
	if (line[i] && line[i] == quote)
		*op = 0;
	return (i);
}

t_operat	check_quotes(char *line)
{
	t_operat	op;
	int			i;

	op.dbl_quote = 0;
	op.sgl_quote = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			i = checking_quotes(&op.sgl_quote, line, i, '\'');
		else if (line[i] == '"')
			i = checking_quotes(&op.dbl_quote, line, i, '"');
		if (!line || !line[i])
			return (op);
		i++;
	}
	return (op);
}
