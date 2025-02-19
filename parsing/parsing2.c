/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenchel <abenchel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 02:14:13 by abenchel          #+#    #+#             */
/*   Updated: 2024/10/06 21:22:22 by abenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_command_redirout(t_command *cmd, t_elem **current)
{
	if ((*current)->type == REDIR_OUT)
		parse_command_redirout_utile(cmd, current, OUT_FILE);
	else
		parse_command_redirout_utile(cmd, current, APP);
}

void	parse_command_redir_in(t_command *cmd, t_elem **current)
{
	(*current) = (*current)->next;
	while ((*current)->type == WHITE_SPACE)
		(*current) = (*current)->next;
	if ((*current)->type == WORD)
	{
		ft_lstadd_back(&cmd->input_files, ft_lstnew((*current)->content));
	}
}

void	parse_command_heredoc(t_command *cmd, t_elem **current)
{
	t_list	*new;

	new = NULL;
	(*current) = (*current)->next;
	while ((*current)->type == WHITE_SPACE)
		(*current) = (*current)->next;
	if ((*current)->type == WORD)
	{
		new = ft_lstnew((*current)->content);
		if ((*current) && (*current)->state == GENERAL)
			new->state = GENERAL;
		else
			new->state = NGENERAL;
		ft_lstadd_back(&cmd->heredoc_delimiters, new);
	}
	return ;
}

void	parse_command_pipe(t_command **cmd)
{
	t_command	*next_cmd;

	(*cmd)->pipe_out = 1;
	next_cmd = new_command();
	(*cmd)->next = next_cmd;
	(*cmd) = (*cmd)->next;
	(*cmd)->arg_count = 0;
}

void	cmpl_pars(t_command *cr, t_elem **elem)
{
	fill_args(cr);
	ft_lstclear_elem(elem);
}
