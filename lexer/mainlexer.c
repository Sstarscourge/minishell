/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainlexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenchel <abenchel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 02:44:25 by abenchel          #+#    #+#             */
/*   Updated: 2024/10/08 10:12:26 by abenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalpha(char c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

int	redir_in(char *str, int i)
{
	return ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '<' && str[i
				+ 1] != '<'));
}

int	redir_out(char *str, int i)
{
	return ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '>' && str[i
				+ 1] != '>'));
}

t_elem	*lexer_command(char *str)
{
	t_elem	*elem;
	int		i;

	elem = NULL;
	i = 0;
	str = ft_strtrim(str, " \t");
	while (str[i])
	{
		if (str[i] == ' ')
			lexer_space(&elem, &i);
		else if (str[i] == '|')
			lexer_pipe(&elem, &i);
		else if (str[i] == '"' || str[i] == '\'')
			lexer_quote(&elem, &i, str);
		else if (redir_in(str, i))
			lexer_redirin(&elem, &i, str);
		else if (redir_out(str, i))
			lexer_redirout(&elem, &i, str);
		else if (str[i] == '-' && ft_isalpha(str[i + 1]))
			lexer_flag(&elem, &i, str);
		else
			lexer_utile(&elem, &i, str);
	}
	free(str);
	return (elem);
}
