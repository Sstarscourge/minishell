/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:55:47 by fidriss           #+#    #+#             */
/*   Updated: 2024/09/13 12:31:45 by fidriss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_child_process(t_command *current, t_command *cmd, 
		int pfd[2], int prev_pfd[2], char **envp, t_env *env)
{
	(void)env;
	if (current->heredoc_delimiters)
		handle_heredoc_redirections(current);
	if (current->next)
	{
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
	}
	if (current != cmd && current->heredoc_delimiters == NULL)
	{
		dup2(prev_pfd[0], STDIN_FILENO);
		close(prev_pfd[0]);
	}
	if (prev_pfd[1] != -1)
		close(prev_pfd[1]);
	if (pfd[0] != -1)
		close(pfd[0]);

	handle_redirections(current);

	// if (built_in_execution(current, env))
	// 	exit(1);
	// else
	execve(current->full_path, current->args, envp);
}

void	execute_parent_process(int prev_pfd[2], int pfd[2])
{
	if (prev_pfd[0] != -1)
		close(prev_pfd[0]);
	if (prev_pfd[1] != -1)
		close(prev_pfd[1]);

	prev_pfd[0] = pfd[0];
	prev_pfd[1] = pfd[1];
	wait(NULL);
}

void	execute_pipeline(t_command *cmd, char **envp, t_env *env)
{
	int			pfd[2];
	int			prev_pfd[2];
	int			pid;
	t_command	*current;

	current = cmd;
	prev_pfd[0] = -1;
	prev_pfd[1] = -1;
	while (current)
	{
		if (current->next)
			create_pipe(pfd);
		pid = fork();
		if (pid == -1)
			exit(1);
		else if (pid == 0)
			execute_child_process(current, cmd, pfd, prev_pfd, envp, env);
		else
			execute_parent_process(prev_pfd, pfd);

		current = current->next;
	}

	close_remaining_pipes(prev_pfd, pfd);
}

void	execute_command(t_command *cmd, char **envp, t_env *env)
{
	int			pid;
	t_command	*current;

	current = cmd;
	pid = fork();
	(void)env;
	if (pid == 0)
	{
		if (cmd->heredoc_delimiters)
			handle_heredoc_redirections(cmd);
		if (current->input_files)
			handle_input_redirection(current->input_files);
		if (current->oa_files)
			handle_output_redirection(current->oa_files);
		// if (built_in_execution(current, env))
		// 	exit(1);
		// else
		execve(current->full_path, current->args, envp);
	}
	else
		wait(NULL);
}

void	ft_execute(t_command *cmd, char **envp, t_env *env)
{
	int		i;

	i = 0;
	if (!cmd)
		return ;
	if (!cmd->pipe_out)
		execute_command(cmd, envp, env);
	else
		execute_pipeline(cmd, envp, env);
}

int main(int ac, char **av, char **envp)
{
    t_env	*env;
    t_command	*cmd;
    char	*line;

    (void)ac;
    (void)av;
    line = NULL;
    env = env_fill(envp);
	envp = list_to_pointer(env);
	signal(SIGINT, SIG_IGN);
    while ((line = readline("minishell$ "))) // Loop to keep the shell running
    {
		add_history(line); // Add the line to the history
		cmd = malloc(sizeof(t_command));
		cmd->command = "cat";
		cmd->full_path = "/bin/cat";
		cmd->args = malloc(sizeof(char **));
		cmd->args[0] = "cat";
		cmd->args[1] = NULL;
		cmd->arg_count = 1;
		cmd->input_files = malloc(sizeof(t_list));
		cmd->input_files->content = "a";
		cmd->input_files->next = malloc(sizeof(t_list));
		cmd->input_files->next->content = "b";
		cmd->input_files->next->next = NULL;
		cmd->oa_files = malloc(sizeof(t_list));
		cmd->oa_files->content = "c";
		cmd->oa_files->next = malloc(sizeof(t_list));
		cmd->oa_files->next->content = "d";
		cmd->oa_files->next->next = NULL;
		cmd->heredoc_delimiters = malloc(sizeof(t_list));
		cmd->heredoc_delimiters->content = "e";
		cmd->heredoc_delimiters->next = malloc(sizeof(t_list));
		cmd->heredoc_delimiters->next->content = "f";
		cmd->heredoc_delimiters->next->next = NULL;
		cmd->heredoc_content = NULL;
		cmd->pipe_out = 1;
		cmd->next = malloc(sizeof(t_command));
		cmd->next->command = "ls";
		cmd->next->full_path = "/bin/ls";
		cmd->next->args = malloc(sizeof(char **));
		cmd->next->args[0] = "ls";
		cmd->next->args[1] = NULL;
		cmd->next->arg_count = 1;
		cmd->next->input_files = NULL;
		cmd->next->oa_files = NULL;
		cmd->next->heredoc_delimiters = malloc(sizeof(t_list));
		cmd ->next->heredoc_delimiters->content = "a";
		cmd->next->heredoc_delimiters->next = malloc(sizeof(t_list));
		cmd->next->heredoc_delimiters->next->content = "b";
		cmd->next->heredoc_delimiters->next->next = NULL;
		cmd->next->heredoc_content = NULL;
		cmd->next->pipe_out = 1;
		cmd->next->next = malloc (sizeof(t_command));
		cmd->next->next->command = "cat";
		cmd->next->next->full_path = "/bin/cat";
		cmd->next->next->args = malloc(sizeof(char **));
		cmd->next->next->args[0] = "cat";
		cmd->next->next->args[1] = NULL;
		cmd->next->next->input_files = NULL;
		cmd->next->next->oa_files = NULL;
		cmd->next->next->heredoc_delimiters = malloc(sizeof(t_list));
		cmd->next->next->heredoc_delimiters->content = "a";
		cmd->next->next->heredoc_delimiters->next = malloc(sizeof(t_list));
		cmd->next->next->heredoc_delimiters->next->content = "b";
		cmd->next->next->heredoc_delimiters->next->next = NULL;
		cmd->next->next->heredoc_content = NULL;
		cmd->next->next->pipe_out = 0;
		cmd->next->next->next = NULL;
		ft_execute(cmd, envp, env);

        // Free the command structs
        free(cmd);
        // Free the line
        free(line);
		ft_free_env(envp);
		exit(1);
	}
    return 0;
}