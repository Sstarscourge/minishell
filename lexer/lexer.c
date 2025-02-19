/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenchel <abenchel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 12:36:44 by abenchel          #+#    #+#             */
/*   Updated: 2024/10/07 08:14:08 by abenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lexer_space(t_elem **elem, int *i)
{
	t_elem	*elem2;

	elem2 = ft_lstnew_elem(" ");
	elem2->state = GENERAL;
	elem2->type = WHITE_SPACE;
	ft_lstadd_back_elem(elem, elem2);
	(*i)++;
}

void	lexer_quote(t_elem **elem, int *i, char *str)
{
	int		j;
	t_elem	*elem2;
	char	*s;

	s = NULL;
	elem2 = NULL;
	if (str[*i] == '"')
	{
		j = (*i) + 1;
		(*i) += skip_quote(&str[(*i)], '\"');
		s = ft_substr(str, j, (*i) - j - 1);
		elem2 = ft_lstnew_elem(s);
		elem2->state = IN_DQUOTE;
	}
	else if (str[(*i)] == '\'')
	{
		j = (*i) + 1;
		(*i) += skip_quote(&str[(*i)], '\'');
		s = ft_substr(str, j, (*i) - j - 1);
		elem2 = ft_lstnew_elem(s);
		elem2->state = IN_QUOTE;
	}
	free(s);
	elem2->type = WORD;
	ft_lstadd_back_elem(elem, elem2);
}

void	lexer_redirin(t_elem **elem, int *i, char *str)
{
	t_elem	*elem2;

	if ((str[(*i)] == '<' && str[(*i) + 1] == '<'))
	{
		elem2 = ft_lstnew_elem("<<");
		elem2->state = GENERAL;
		elem2->type = HERE_DOC;
		ft_lstadd_back_elem(elem, elem2);
		(*i) += 2;
	}
	else if (str[(*i)] == '<' && str[(*i) + 1] != '<')
	{
		elem2 = ft_lstnew_elem("<");
		elem2->state = GENERAL;
		elem2->type = REDIR_IN;
		ft_lstadd_back_elem(elem, elem2);
		(*i)++;
	}
}
