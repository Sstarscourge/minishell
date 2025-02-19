/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 02:45:18 by abenchel          #+#    #+#             */
/*   Updated: 2024/10/06 22:53:49 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lexer_redirout(t_elem **elem, int *i, char *str)
{
	t_elem	*elem2;

	if ((str[(*i)] == '>' && str[(*i) + 1] == '>'))
	{
		elem2 = ft_lstnew_elem(">>");
		elem2->state = GENERAL;
		elem2->type = APPEND;
		ft_lstadd_back_elem(elem, elem2);
		(*i) += 2;
	}
	else if (str[(*i)] == '>' && str[(*i) + 1] != '>')
	{
		elem2 = ft_lstnew_elem(">");
		elem2->state = GENERAL;
		elem2->type = REDIR_OUT;
		ft_lstadd_back_elem(elem, elem2);
		(*i)++;
	}
}

void	lexer_flag(t_elem **elem, int *i, char *str)
{
	int		j;
	t_elem	*elem2;
	char	*s;

	j = (*i);
	(*i)++;
	while (str[(*i)] && ft_isalpha(str[(*i)]) && str[(*i)] != ' ')
		(*i)++;
	s = ft_substr(str, j, (*i) - j);
	elem2 = ft_lstnew_elem(s);
	free(s);
	elem2->state = GENERAL;
	elem2->type = FLAG;
	ft_lstadd_back_elem(elem, elem2);
}

void	lexer_pipe(t_elem **elem, int *i)
{
	t_elem	*elem2;

	elem2 = ft_lstnew_elem("|");
	elem2->state = GENERAL;
	elem2->type = PIPE_LINE;
	ft_lstadd_back_elem(elem, elem2);
	(*i)++;
}

void	lexer_utile(t_elem **elem, int *i, char *str)
{
	int		j;
	t_elem	*elem2;
	char	*s;

	j = (*i);
	while (str[(*i)] && str[(*i)] != ' ' && str[(*i)] != '|')
	{
		if (str[(*i)] == '"' || str[(*i)] == '\'' || str[(*i)] == '<'
			|| str[(*i)] == '>')
			break ;
		(*i)++;
	}
	s = ft_substr(str, j, (*i) - j);
	elem2 = ft_lstnew_elem(s);
	free(s);
	elem2->state = GENERAL;
	elem2->type = WORD;
	ft_lstadd_back_elem(elem, elem2);
}

void	combine(t_elem **elm)
{
	t_elem	*current;
	t_elem	*next;

	current = *elm;
	while (current && current->next != NULL)
	{
		next = current->next;
		if ((current->type == WORD || current->type == FLAG)
			&& next->type == WORD)
		{
			current->content = ft_strjoin(current->content, next->content, 2);
			if (next->state != GENERAL)
				current->state = next->state;
			current->next = next->next;
			free(next);
		}
		else
			current = current->next;
	}
}
