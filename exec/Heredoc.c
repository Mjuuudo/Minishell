/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:21:46 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/18 23:38:01 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

void process_heredoc_input(int fd, char *delimiter, t_envvar *envp)
{
    char *line;

    // printf("process_heredoc_input: Starting heredoc for delimiter '%s'\n", delimiter);
    while (1)
    {
        signal(SIGINT, heredoc_sigint_handler);
        line = readline(">");
        if (!line)
        {
            printf("process_heredoc_input: Received EOF (Ctrl+D)\n");
            break;
        }
        // printf("process_heredoc_input: Read line: '%s'\n", line);

        line = ft_expandherdoc(line, envp);
        // printf("process_heredoc_input: Expanded line: '%s'\n", line);

        if (ft_strcmp(line, delimiter) == 0)
        {
            // printf("process_heredoc_input: Delimiter matched. Exiting loop.\n");
            free(line);
            break;
        }
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        // printf("process_heredoc_input: Written line to fd = %d\n", fd);
        free(line);
		// return(fd);
    }
    // printf("process_heredoc_input: Exiting heredoc\n");
}


void	handle_heredoc_redirections(int fd,t_redirection *red, t_cmd *cmd,
		t_envvar *envp)
{
	int	i;
	// int	fd;

	i = 0;
	while (red)
	{
		if (red->identifier == 5)
		{

			// printf("after creation -----> shell.temp_file = %s\n", shell.temp_file);
			// printf("implement_heredoc: Temporary file for heredoc: %s\n", shell.temp_file);
			process_heredoc_input(fd, red->file, envp);
			close(fd);
		}
		i++;
		red = red->next;
	}
	// return(fd);
}

void	process_all_heredocs(int fd, t_cmd *cmd, t_envvar *envp)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		handle_heredoc_redirections(fd,current->red, current, envp);
		current = current->next;
	}
	// return(fd);
}

int implement_heredoc(t_cmd *cmd, t_envvar *envp)
{
    int pid;
    int status;
	int fd;

    // printf("implement_heredoc: Starting heredoc implementation\n");
	fd = set_files(cmd);
    pid = fork();
    if (pid == 0)
    {
        // printf("implement_heredoc: Child process started\n");
        process_all_heredocs(fd,cmd, envp);
		ft_freeenv(shell.envp);
		ft_freeenvholder(shell.envholder);
        // printf("implement_heredoc: Child process exiting\n");
        exit(0);
    }
    else if (pid == -1)
    {
        perror("Fork failed");
        return (1);
    }
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
    {
        // printf("implement_heredoc: Child exited with status %d\n", WEXITSTATUS(status));
        status = WEXITSTATUS(status);
    }
    else if (WIFSIGNALED(status))
    {
        // printf("implement_heredoc: Child terminated by signal %d\n", WTERMSIG(status));
        status = WTERMSIG(status) + 128;
    }
    return (status);
}

bool set_redirections(t_redirection *file)
{
	int fd;
	int i = 0;

	while (file)
	{
		fd = open_file(file, i);
		if (fd == -1)
			return false;

		if (!set_fd(file, fd))
		{
			close(fd);
			return false;
 		}

		close(fd);
		file = file->next;
		i++;
	}
	return true;
}

int	execute_cmd(t_cmd *cmd)
{
	pid_t	pid;
	int		status = 0;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (!set_redirections(cmd->red))
			exit(1);
		if (!execute_builtin(cmd))
		{
			if (ft_strchr('/', cmd->order))
				execute_without_path(cmd);
			else
				execute_with_path(cmd);
		}
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = WTERMSIG(status) + 128;
	signal(SIGINT, SIG_IGN);
	// ft_freeenv(shell.envp);
	// ft_freeenvholder(shell.envholder);
	return (0);
}

int open_file(t_redirection *file, int index)
{
    int fd;
	// printf("file->file = %s\n", file->file);
	if (file->identifier == LESS)
	{
        fd = open(file->file, O_RDONLY, 0644);
	}
    else if (file->identifier == LLESS)
    {
		printf("shell.temp_file = %s\n", shell.temp_file);
        fd = open(shell.temp_file, O_RDONLY, 0644);
    }
    else if (file->identifier == GREAT)
        fd = open(file->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (file->identifier == DGREAT)
        fd = open(file->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        fd = -1;

    if (fd == -1)
        perror("minishell01$");
    return fd;
}

bool set_fd(t_redirection *file, int fd)
{
    if (file->identifier == LESS || file->identifier == LLESS)
    {
        if (dup2(fd, STDIN_FILENO) == -1)
        {
            perror("minishell02$");
            return false;
        }
    }
    else
    {
        if (dup2(fd, STDOUT_FILENO) == -1)
        {
            perror("minishell02$");
            return false;
        }
    }
	// printf("set_fd: Redirected fd %d to STDIN\n", fd);
    return true;
}

void	reset_redirections(void)
{
	int	fd;

	fd = open("/dev/tty", O_RDWR);
	dup2(fd, STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

