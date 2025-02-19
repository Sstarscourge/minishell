/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:23:23 by abenchel          #+#    #+#             */
/*   Updated: 2024/10/06 22:17:13 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_existing_node(t_env **env, char *arg)
{
	t_env	*node;
	char	*tmp;
	char	*tmp2;

	tmp2 = before_equal_sign(arg);
	tmp = after_equal_sign(arg);
	if (tmp)
	{
		free(tmp);
		node = find_node(*env, tmp2);
		free (tmp2);
		if (node->value)
			free(node->value);
		node->value = after_equal_sign(arg);
	}
	else
		free (tmp2);
}

void	handle_new_node(t_env **env, char *arg)
{
	t_env	*node;

	node = create_new_node(arg);
	if (node && node->name)
		add_env(env, node);
	else if (node)
		free(node);
}

int	check_special_characters(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=')
		return (1);
	if (str[0] == '\0')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (i == 0 && !ft_isalpha(str[i]) && str[i] != '_')
			return (1);
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	process_args(t_command *cmd, t_env **env)
{
	int	i;

	i = 1;
	while (cmd->argsp[i])
	{
		if (check_special_characters(cmd->argsp[i]) == 1)
			return (-1);
		if (check_existing_node(*env, cmd->argsp[i]))
			handle_existing_node(env, cmd->argsp[i]);
		else
			handle_new_node(env, cmd->argsp[i]);
		i++;
	}
	return (0);
}

int	ft_export(t_command *cmd, t_env **env)
{
	if (!cmd->argsp[1])
	{
		print_export(*env);
		return (0);
	}
	if (process_args(cmd, env) == -1)
	{
		print_error("not a valid identifier", cmd->argsp[1]);
		return (1);
	}
	return (0);
}
