/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:58:02 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/23 01:26:28 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

static int	open_input_file(t_redirection file, int i, t_types type)
{
	int	fd;

	if (type == 4)
	{
		fd = open(file.file, O_RDONLY, 0644);
	}
	else if (type == 5 && shell.temp_file)
	{
		fd = open(shell.temp_file, O_RDONLY);
		if (fd == -1)
			perror("minishell: Failed to open heredoc temp file");
	}
	else
	{
		fd = -1;
	}
	return (fd);
}

static int	open_output_file(t_redirection *file)
{
	int	fd;

	if (file->identifier == GREAT)
		fd = open(file->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

static bool	handle_redirection(t_redirection *file, int fd)
{
	if (file->identifier == LESS || file->identifier == LLESS)
		dup2(fd, STDIN_FILENO);
	else if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell02$");
		return (false);
	}
	return (true);
}

bool	set_redirections(t_redirection *file)
{
	int	fd;
	int	i;

	i = 0;
	while (file)
	{
		if (file->identifier == LESS)
			fd = open_input_file(*file, i, 4);
		else if (file->identifier == LLESS)
			fd = open_input_file(*file, i, 5);
		else
			fd = open_output_file(file);
		if (fd == -1)
		{
			perror("minishell01$:");
			return (false);
		}
		if (!handle_redirection(file, fd))
			return (false);
		close(fd);
		file = file->next;
		i++;
	}
	return (true);
}

void	reset_redirections(void)
{
	int	fd;

	fd = open("/dev/tty", O_RDWR);
	dup2(fd, STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
