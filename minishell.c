#include "minishell.h"

// int	main(int ac, char **av, char **envp)
// {
// 	t_env	*env;
// 	char	*line;

// 	(void)ac;
// 	(void)av;
// 	env = env_fill(envp);
// 	while (1)
// 	{
// 		line = readline("minishell$ ");
// 		while (env)
// 		{
// 			printf("%s=%s\n", env->name, env->value);
// 			env = env->next;
// 		}
// 		if (!line)
// 			break ;
// 		add_history(line);
// 		free(line);
// 	}
// }

t_env	*env_fill(char **envp)
{
	t_env	*env;
	t_env	*tmp;
	int		i;

	if (!envp)
		return (NULL);
	i = 0;
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	tmp = env;
	while (envp[i])
	{
		tmp->name = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
		tmp->value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		if (envp[i + 1])
		{
			tmp->next = malloc(sizeof(t_env));
			tmp = tmp->next;
		}
		else
			tmp->next = NULL;
		i++;
	}
	return (env);
}

char	**list_to_pointer(t_env *env)
{
	char	**tab;
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	tab = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env)
	{
		tab[i] = ft_strjoin(env->name, "=");
		tab[i] = ft_strjoin(tab[i], env->value);
		i++;
		env = env->next;
	}
	tab[i] = NULL;
	return (tab);
}
