/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:30:14 by fidriss           #+#    #+#             */
/*   Updated: 2024/10/14 20:44:34 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_slash_command(char *commd, char **env)
{
	check_directory(commd);
	if (access(commd, X_OK) == 0)
		return (commd);
	else if (access(commd, F_OK) == 0)
	{
		free_array(env);
		print_error("Permission denied", commd);
		exit(126);
	}
	print_error("No such file or directory.", commd);
	free_array(env);
	exit(127);
}

char	*check_command_access(char *string, char *commd, char **env)
{
	if (access(string, X_OK) == 0)
		return (string);
	if (access(string, F_OK) == 0)
	{
		print_error("Permission denied", commd);
		free_array(env);
		free(string);
		exit(126);
	}
	if (string)
		free(string);
	return (NULL);
}

char	*find_command_in_path(char **p, char *commd, char **env)
{
	int		i;
	char	*string;
	char	*result;

	i = 0;
	string = NULL;
	while (p[i])
	{
		p[i] = ft_strjoin(p[i], "/", 1);
		string = ft_strjoin(p[i], commd, 1);
		check_directory(string);
		result = check_command_access(string, commd, env);
		if (result)
			return (result);
		i++;
	}
	free_array(env);
	print_error("Command not found", commd);
	exit(127);
}

char	*is_execute(char *commd, char **env, t_env **envp)
{
	char	*s;
	char	**p;
	t_env	*tmp;

	if (ft_strchr(commd, '/'))
		return (handle_slash_command(commd, env));
	tmp = find_node(*envp, "PATH");
	if (!tmp)
		return (NULL);
	s = tmp->value;
	p = ft_split(s, ':');
	return (find_command_in_path(p, commd, env));
}
