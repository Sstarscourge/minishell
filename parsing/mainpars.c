/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainpars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 02:19:13 by abenchel          #+#    #+#             */
/*   Updated: 2024/10/14 21:42:55 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_par(t_utile *utl)
{
	if (utl->current->type == WORD && !utl->cmd->command)
		return (1);
	if (utl->current->type == FLAG || utl->current->type == WORD) 
		return (2);
	return (0);
}

t_command	*parse_command(t_elem *elem)
{
	t_utile	utl;

	utl.cmd = new_command();
	utl.cr = utl.cmd;
	utl.current = elem;
	while (utl.current)
	{
		if (if_par(&utl) == 1)
			parse_command_in(utl.cmd, utl.current);
		else if (if_par(&utl) == 2)
			parse_command_flag(utl.cmd, utl.current);
		else if (utl.current->type == REDIR_IN)
			parse_command_redir_in(utl.cmd, &utl.current);
		else if (utl.current->type == APPEND || utl.current->type == REDIR_OUT)
			parse_command_redirout(utl.cmd, &utl.current);
		else if (utl.current->type == HERE_DOC)
			parse_command_heredoc(utl.cmd, &utl.current);
		else if (utl.current->type == PIPE_LINE)
			parse_command_pipe(&utl.cmd);
		if (!utl.current)
			break ;
		utl.current = utl.current->next;
	}
	cmpl_pars(utl.cr, &elem);
	return (utl.cr);
}
