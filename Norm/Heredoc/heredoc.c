/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 08:16:53 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/20 22:32:13 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

int	count_heredoc(t_cmd *cmd)
{
	int				heredoc_counter;
	t_cmd			*current;
	t_redirection	*temp;

	heredoc_counter = 0;
	current = shell.cmd;
	temp = current->red;
	while (current)
	{
		if (temp)
		{
			while (temp)
			{
				if (temp->identifier == 5)
					heredoc_counter++;
				temp = temp->next;
			}
		}
		current = current->next;
	}
	if (heredoc_counter > 16)
		printf("minishell$: maximum here-document count exceded\n");
	return (heredoc_counter);
}

static void	process_heredoc_line(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		signal(SIGINT, heredoc_sigint_handler);
		line = readline(">");
		if (!line)
			break ;
		line = ft_expandherdoc(line, shell.envp);
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

static void	process_heredoc(t_redirection *temp, t_cmd *cmd)
{
	int	i;
	int	fd;

	i = 0;
	while (temp)
	{
		if (temp->identifier == 5)
		{
			fd = set_files(cmd, i);
			process_heredoc_line(fd, temp->file);
			close(fd);
		}
		i++;
		temp = temp->next;
	}
}

static void	handle_child_process(t_cmd *cmd)
{
	t_cmd			*current;
	t_redirection	*temp;

	current = shell.cmd;
	while (current)
	{
		temp = current->red;
		process_heredoc(temp, cmd);
		current = current->next;
	}
	ft_malloc(0, 'f');
	exit(0);
}

int	implement_heredoc(t_cmd *cmd)
{
	int	pid;
	int	status;
	int	count;

	count = count_heredoc(cmd);
	status = -1;
	if (count > 16)
	{
		ft_malloc(0, 'f');
		exit(2);
	}
	else if (count == 0)
		return (0);
	pid = fork();
	if (pid == 0)
		handle_child_process(cmd);
	else if (pid == -1)
		perror("Fork failed");
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = WTERMSIG(status) + 128;
	return (status);
}
