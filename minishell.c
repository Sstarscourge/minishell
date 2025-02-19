/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:36:51 by abenchel          #+#    #+#             */
/*   Updated: 2024/10/14 22:17:14 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_command(t_command **cmd)
{
	t_command	*current;

	current = *cmd;
	free(current->command);
	free_array(current->argsp);
	ft_lstclear_list(&current->input_files);
	ft_lstclear_list(&current->oa_files);
	ft_lstclear_list(&current->heredoc_delimiters);
	if (current->full_path)
		free(current->full_path);
	*cmd = (*cmd)->next;
	free (current);
}

void	handle_line_null(char **line, t_env **evp)
{
	free(*line);
	ft_lstclear_envp(evp);
	exit(0);
}

void	handle_line_empty(char **line)
{
	free(*line);
	*line = NULL;
}

void	process_line(char **line, char **envp, t_env **evp, int *exit_stat)
{
	t_elem		*env;
	t_command	*cmd;
	int			stat;

	if (line && *line)
		add_history(*line);
	signal(SIGINT, SIG_IGN);
	*line = check_error(*line, exit_stat);
	if (*line != NULL)
	{
		g_signal = 0;
		env = lexer_command(*line);
		expand(env, *evp, *exit_stat);
		combine(&env);
		cmd = parse_command(env);
		if (!cmd)
			exit(0);
		*line = NULL;
		ft_execute(cmd, envp, evp, &stat);
		*exit_stat = stat;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env		*evp;
	char		*line;
	static int	exit_stat;

	(void)ac;
	(void)av;
	evp = env_fill(envp);
	line = NULL;
	signal(SIGQUIT, SIG_IGN);
	exit_stat = 0;
	while (1)
	{
		signal(SIGINT, handle_sigint);
		line = readline("minishell$ ");
		line = ft_strtrim(line, " \t");
		if (!line)
			handle_line_null(&line, &evp);
		else if (*line == '\0')
			handle_line_empty(&line);
		else
			process_line(&line, envp, &evp, &exit_stat);
	}
}
