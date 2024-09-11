/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 01:29:25 by fidriss           #+#    #+#             */
/*   Updated: 2024/09/10 10:45:01 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_env(t_list *env, char *name)
{
	t_list *tmp;
	char *str;		
	int i;

	tmp = env;
	while (tmp)
	{
		i = 0;
		str = tmp->content;
		while (str[i] && str[i] != '=')
			i++;
		if (strncmp(str, name, i) == 0)
			return (str + i + 1);
		tmp = tmp->next;
	}
	return (NULL);
}

t_list *find_node(t_list *env, char *name)
{
	t_list *tmp;
	char *str;
	int i;

	tmp = env;
	while (tmp)
	{
		i = 0;
		str = tmp->content;
		while (str[i] && str[i] != '=')
			i++;
		if (strncmp(str, name, i) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void change_pwd(t_list *env)
{
	char	*pwd;
	char	*str;
	t_list	*tmp;

	pwd = getcwd(NULL, 0);
	str = ft_strjoin("PWD=", pwd);
	tmp = find_node(env, "PWD");
	if (tmp)
	{
		free(tmp->content);
		tmp->content = str;
	}
}

void change_oldpwd(t_list *env)
{
	char *oldpwd;
	char *str;
	t_list *tmp;

	oldpwd = get_env(env, "PWD");
	str = ft_strjoin("OLDPWD=", oldpwd);
	tmp = find_node(env, "OLDPWD");
	if (tmp)
	{
		free(tmp->content);
		tmp->content = str;
	}
}

int	 ft_cd(t_command *cmd, t_list *env)
{
	char	*path;

	if (cmd->arg_count == 1)
	{
		path = ft_strdup(get_env(env, "HOME"));
		if (chdir(path) == -1)
		{
			free(path);
			printf("minishell: cd: HOME not set\n");
			return (1);
		}
		free(path);
	}
	else
	{
		path = ft_strdup(cmd->args[1]);
		if (chdir(path) == -1)
		{
			free(path);
			printf("minishell: cd: %s: No such file or directory\n", 
				cmd->args[1]);
			return (1);
		}
		free(path);
	}
	change_oldpwd(env);
	change_pwd(env);
	return (0);
}

int main(int ac, char **av, char **environ)
{
	(void)ac;
	(void)av;
	t_list *env;
	t_command *cmd;

	env = env_fill(environ);
	cmd = malloc(sizeof(t_command));
	cmd->arg_count = 2;
	cmd->args = malloc(sizeof(char *) * 2);
	cmd->args[0] = ft_strdup("cd");
	cmd->args[1] = ft_strdup("test");
	ft_cd(cmd, env);
	printf("%s\n", get_env(env, "PWD"));
	printf("%s\n", get_env(env, "OLDPWD"));
	return (0);
}