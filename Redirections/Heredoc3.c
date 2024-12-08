/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heredoc3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:51:17 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/07 12:43:33 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

void	pid_is_0(char *input_file, char *cmd, t_envvar *envp, t_shell *shell)
{
	int	input_fd;

	input_fd = open(input_file, O_RDONLY);
	if (input_fd < 0)
	{
		perror("Failed to open heredoc input file");
		exit(1);
	}
	if (dup2(input_fd, STDIN_FILENO) == -1)
	{
		perror("Failed to redirect stdin");
		close(input_fd);
		exit(1);
	}
	close(input_fd);
	run_simplecmd(shell, envp, &cmd);
	exit(0);
}

void	execute_command_with_heredoc(char *input_file, char *cmd,
		t_envvar *envp, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		pid_is_0(input_file, cmd, envp, shell);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
	}
	else
		perror("Fork failed");
}

void process_heredoc_input(char *delimiter, char *filename)
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("Failed to open heredoc temp file");
        return;
    }

    char *line;
    while (1)
    {
        line = readline(">");
        if (!line)  // Ctrl+D or error
        {
            break;
        }

        if (strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }

        // Write line to file with newline
        ssize_t write_result = write(fd, line, strlen(line));
        write(fd, "\n", 1);
        
        free(line);

        if (write_result < 0)
        {
            perror("Error writing to heredoc file");
            break;
        }
    }

    close(fd);
}
