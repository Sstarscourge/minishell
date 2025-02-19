/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:00:33 by fidriss           #+#    #+#             */
/*   Updated: 2024/10/11 14:55:51 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_dollar_sign(char **str, t_env *envp, int *i, t_command *cmd)
{
	char	*new_str;
	char	*tmp;

	(*str)++;
	if (**str == '?')
	{
		new_str = ft_itoa(cmd->exit_status);
		(*str)++;
	}
	else if (**str == '\0')
	{
		return (ft_strdup("$"));
	}
	else
	{
		new_str = beforedolaar(*str, i);
		tmp = env_string(new_str, envp);
		new_str = tmp;
	}
	return (new_str);
}

char	*handle_character(char **str, t_env *envp, int *i, t_command *cmd)
{
	char	*new_str;

	if (**str == '$')
		new_str = handle_dollar_sign(str, envp, i, cmd);
	else if (ft_isalpha(**str))
		new_str = beforedolaar(*str, i);
	else
	{
		new_str = makestring(**str);
		(*str)++;
	}
	return (new_str);
}

char	*expand_line(char *line, t_env *envp, t_command *cmd)
{
	char	*new_str;
	int		i;
	char	*returnstr;
	char	*str;

	i = 0;
	returnstr = ft_strdup("");
	str = line;
	while (*str)
	{
		i = 0;
		new_str = handle_character(&str, envp, &i, cmd);
		returnstr = ft_strjoin(returnstr, new_str, 2);
		str += i;
	}
	free(line);
	line = NULL;
	return (returnstr);
}
