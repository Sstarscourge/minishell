/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 22:46:39 by abenchel          #+#    #+#             */
/*   Updated: 2024/10/14 22:14:09 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstclear_cmd(t_command **cmd)
{
	t_command	*cmd2;

	while (*cmd)
	{
		cmd2 = *cmd;
		*cmd = (*cmd)->next;
		free(cmd2->command);
		free_array((*cmd)->argsp);
		ft_lstclear_list(&(cmd2->heredoc_delimiters));
		ft_lstclear_list(&(cmd2->oa_files));
		ft_lstclear_list(&(cmd2->input_files));
		free(cmd2);
	}
}

t_command	*new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->command = NULL;
	cmd->full_path = NULL;
	cmd->args = NULL;
	cmd->argsp = NULL;
	cmd->arg_count = 0;
	cmd->input_files = NULL;
	cmd->oa_files = NULL;
	cmd->heredoc_delimiters = NULL;
	cmd->heredoc_content = NULL;
	cmd->pipe_out = 0;
	cmd->exit_status = 0;
	cmd->next = NULL;
	return (cmd);
}

void	parse_command_in(t_command *cmd, t_elem *current)
{
	cmd->command = ft_strdup(current->content);
	ft_lstadd_back(&cmd->args, ft_lstnew(current->content));
	cmd->arg_count++;
}

void	parse_command_flag(t_command *cmd, t_elem *current)
{
	if (!cmd->command)
	{
		cmd->command = ft_strdup((current)->content);
		ft_lstadd_back(&cmd->args, ft_lstnew((current)->content));
		cmd->arg_count++;
	}
	else
	{
		ft_lstadd_back(&cmd->args, ft_lstnew((current)->content));
		cmd->arg_count++;
	}
}

void	parse_command_redirout_utile(t_command *cmd, t_elem **current, int i)
{
	(*current) = (*current)->next;
	while ((*current)->type == WHITE_SPACE)
		(*current) = (*current)->next;
	if ((*current)->type == WORD)
	{
		ft_lstadd_back(&cmd->oa_files, ft_lstnew((*current)->content));
		ft_lstlast(cmd->oa_files)->type = i;
	}
}
