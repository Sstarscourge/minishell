/* ************************************************************************** */
/*		    */
/*		        :::      ::::::::   */
/*   execution.c		    :+:      :+:    :+:   */
/*		    +:+ +:+         +:+     */
/*   By: fidriss <fidriss@student.42.fr>		+#+  +:+       +#+        */
/*		+#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:04:29 by fidriss           #+#    #+#		 */
/*   Updated: 2024/09/08 21:27:21 by fidriss          ###   ########.fr       */
/*		    */
/* ************************************************************************** */

#include "minishell.h"

void	handle_output_redirection(t_list *output_files)
{
	int	fd;

	fd = -1;
	while (output_files)
	{
		if (fd != -1)
			close(fd);
		if (output_files->type == 1)
			fd = open(output_files->content, O_WRONLY
					| O_CREAT | O_TRUNC, 0644);
		else
			fd = open(output_files->content, O_WRONLY 
					| O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("open");
			exit(1);
		}
		output_files = output_files->next;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
}

void	handle_input_redirection(t_list *input_file)
{
	int	fd;

	fd = -1;
	while (input_file)
	{
		if (fd != -1)
			close(fd);
		fd = open(input_file->content, O_RDONLY);
		if (fd == -1)
		{
			perror("open");
			exit(1);
		}
		input_file = input_file->next;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
}

void	execute_pipeline(t_command *cmd, char **env)
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
		{
			if (pipe(pfd) == -1) 
			{
				perror("pipe");
				exit(1);
			}
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
		{
			if (current->next)
			{
				close(pfd[0]);
				dup2(pfd[1], STDOUT_FILENO);
				close(pfd[1]);
			}
			if (current != cmd)
			{
				dup2(prev_pfd[0], STDIN_FILENO);
				close(prev_pfd[0]);
			}
			if (prev_pfd[1] != -1)
				close(prev_pfd[1]);
			if (pfd[0] != -1)
				close(pfd[0]);
			if (current->input_files)
				handle_input_redirection(current->input_files);
			if (current->oa_files)
				handle_output_redirection(current->oa_files);
			if (execve(current->full_path, current->args, env) == -1)
			{
				perror("execve");
				exit(1);
			}
		}
		else
		{
			if (prev_pfd[0] != -1)
				close(prev_pfd[0]);
			if (prev_pfd[1] != -1)
				close(prev_pfd[1]);
			prev_pfd[0] = pfd[0];
			prev_pfd[1] = pfd[1];
			wait(NULL);
		}
		current = current->next;
	}
	if (prev_pfd[0] != -1)
		close(prev_pfd[0]);
	if (prev_pfd[1] != -1)
		close(prev_pfd[1]);
	close(pfd[0]);
	close(pfd[1]);
}

void	execute_command(t_command *cmd, char **env)
{
    int         pid;
    t_command   *current;

	current = cmd;
	pid = fork();
	if (pid == 0)
	{
		if (current->input_files)
			handle_input_redirection(current->input_files);
		if (current->oa_files)
			handle_output_redirection(current->oa_files);
		execve(current->full_path, current->args, env);
	}
	else
		wait(NULL);
}

void	write_in_file(char *line)
{
	int	fd;

	fd = open("/tmp/heredoc.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	ft_putstr_fd(line, fd);
	write(fd, "\n", 1);
	close(fd);
}

void	handle_heredoc(t_command *cmd)
{
	char	*line;
	int		pid;

	line = NULL;
	while (cmd->heredoc_delimiters)
	{
		unlink("/tmp/heredoc.txt");
		pid = fork();
		if (pid == 0)
		{
			line = readline(">");
			while (ft_strncmp(line, cmd->heredoc_delimiters->content, 
					ft_strlen(cmd->heredoc_delimiters->content)))
			{
				if (cmd->heredoc_delimiters->next == NULL)
					write_in_file(line);
				add_history(line);
				free(line);
				line = readline(">");
			}
			free(line);
			exit(0);
		}
		else
			waitpid(pid, NULL, 0);
		cmd->heredoc_delimiters = cmd->heredoc_delimiters->next;
	}
}

void	ft_execute(t_command *cmd, t_env *env)
{
	char	**envp;
	int		i;

	i = 0;
	if (!cmd)
		return ;
	envp = list_to_pointer(env);
	if (cmd->heredoc_delimiters)
	{
		handle_heredoc(cmd);
	}
	if (!cmd->pipe_out)
	{
		execute_command(cmd, envp);
	}
	else
	{
		execute_pipeline(cmd, envp);
	}
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

    while (1) // Loop to keep the shell running
    {
        line = readline("minishell> "); // Display a prompt and read a line of input
        if (!line)
		break; // Exit the loop if the user types EOF (Ctrl+D)
		add_history(line); // Add the line to the history
		cmd = malloc(sizeof(t_command));
		cmd->command = "hr";
		cmd->full_path = "/baegr";
		cmd->args = malloc(sizeof(char *) * 2);
		cmd->args[0] = "ls";
		cmd->args[1] = NULL;
		cmd->arg_count = 1;
		cmd->pipe_out = 0;
		cmd->input_files = NULL;
		cmd->oa_files = NULL;
		cmd->heredoc_delimiters = malloc(sizeof(t_list));
		cmd->heredoc_delimiters->content = "a";
		cmd->heredoc_content = NULL;
		cmd->heredoc_delimiters->next = malloc(sizeof(t_list));
		cmd->heredoc_delimiters->next->content = "b";
		cmd->heredoc_delimiters->next->next = malloc(sizeof(t_list));
		cmd->heredoc_delimiters->next->next->content = "c";
		cmd->heredoc_delimiters->next->next->next = NULL;
		cmd->next = NULL;
		ft_execute(cmd, env);

        // Free the command structs
        free(cmd);
        // Free the line
        free(line);
    }
    return 0;
}