/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:21:46 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/16 08:54:46 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

void	process_heredoc_input(int fd, char *delimiter, t_envvar *envp)
{
	char	*line;

	while (1)
	{
		signal(SIGINT, heredoc_sigint_handler);
		line = readline(">");
		if (!line)
			break ;
		line = ft_expandherdoc(line, envp);
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

void	handle_heredoc_redirections(t_redirection *red, t_cmd *cmd,
		t_envvar *envp)
{
	int	i;
	int	fd;

	i = 0;
	while (red)
	{
		if (red->identifier == 5)
		{
			fd = set_files(cmd, i);
			process_heredoc_input(fd, red->file, envp);
			close(fd);
		}
		i++;
		red = red->next;
	}
}

void	process_all_heredocs(t_cmd *cmd, t_envvar *envp)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		handle_heredoc_redirections(current->red, current, envp);
		current = current->next;
	}
}

int	implement_heredoc(t_cmd *cmd, t_envvar *envp)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		process_all_heredocs(cmd, envp);
		exit(0);
	}
	else if (pid == -1)
	{
		perror("Fork failed");
		return (1);
	}
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = WTERMSIG(status) + 128;
	return (status);
}
