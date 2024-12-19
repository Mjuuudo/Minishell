/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:58:02 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/19 10:57:37 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

// bool	set_redirections(t_redirection *file)
// {
// 	int	fd, i;

// 	i = 0;
// 	while (file)
// 	{
// 		if (file->identifier == LESS || file->identifier == LLESS)
// 		{
// 			set_files2(shell.cmd, i);
// 			fd = open(shell.temp_file, O_RDONLY, 0644);
// 		}
// 		else if (file->identifier == GREAT)
// 			fd = open(file->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		else if (file->identifier == DGREAT)
// 			fd = open(file->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		if (fd == -1)
// 			return (perror("minishell01$"), false);
// 		if (file->identifier == LESS || file->identifier == LLESS)
// 			dup2(fd, STDIN_FILENO);
// 		else
// 		{
// 			if(dup2(fd, STDOUT_FILENO) == -1)
// 				perror("minishell02$");
// 		}
// 		close(fd);
// 		file = file->next;
// 		i++;
// 	}
// 	return (true);
// }

static int	open_input_file(int i)
{
	int	fd;

	set_files2(shell.cmd, i);
	fd = open(shell.temp_file, O_RDONLY, 0644);
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
		if (file->identifier == LESS || file->identifier == LLESS)
			fd = open_input_file(i);
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
