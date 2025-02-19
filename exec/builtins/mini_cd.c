/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 01:29:25 by fidriss           #+#    #+#             */
/*   Updated: 2024/10/07 16:46:43 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_pwd(t_env **env)
{
	char	*pwd;
	char	*tmp_str;
	t_env	*tmp;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	tmp = find_node(*env, "PWD");
	if (!tmp)
	{
		tmp_str = ft_strjoin("PWD=", pwd, 0);
		free(pwd);
		add_env(env, create_new_node(tmp_str));
		free(tmp_str);
		return ;
	}
	else
	{
		free(tmp->value);
		tmp->value = ft_strdup(pwd);
	}
	free(pwd);
}

void	change_oldpwd(t_env **env)
{
	t_env	*old_pwd;
	t_env	*tmp;
	char	*tmp_str;

	old_pwd = find_node(*env, "PWD");
	if (old_pwd)
	{
		tmp = find_node(*env, "OLDPWD");
		if (!tmp)
		{
			tmp_str = ft_strjoin("OLDPWD=", old_pwd->value, 0);
			tmp = create_new_node(tmp_str);
			free(tmp_str);
			add_env(env, tmp);
		}
		else
		{
			free(tmp->value);
			tmp->value = ft_strdup(old_pwd->value);
		}
	}
}

int	handle_no_args(t_command *cmd, t_env **env)
{
	char	*path;

	path = getenv("HOME");
	if (chdir(path) == -1)
	{
		print_error("HOME not set.", cmd->command);
		return (1);
	}
	change_oldpwd(env);
	change_pwd(env);
	return (0);
}

int	handle_with_args(t_command *cmd, t_env **env)
{
	char	*path;

	path = ft_strdup(cmd->argsp[1]);
	if (chdir(path) == -1)
	{
		if (path)
			free(path);
		print_error("Path not found.", cmd->command);
		return (1);
	}
	if (path)
		free(path);
	change_oldpwd(env);
	change_pwd(env);
	return (0);
}

int	ft_cd(t_command *cmd, t_env **env)
{
	int	i;

	if (cmd->arg_count == 1)
		i = handle_no_args(cmd, env);
	else
		i = handle_with_args(cmd, env);
	return (i);
}
