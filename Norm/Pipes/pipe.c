/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:54:40 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/19 23:35:02 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

int	first_child(t_cmd *cmd, int *fd)
{
	int	pid;
	
	pid = fork();
	if (pid == 0)
	{
		// printf("first child pid %d\n",getpid);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute_cmd(cmd);
		exit(1);
	}
	return (pid);
}

int	second_child(t_cmd *cmd, int *fd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		// printf("second child pid %d\n",getpid);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		ft_execution(cmd);
		exit(1);
	}
	return (pid);
}

int	execute_pipe(t_cmd *cmd)
{
	int		fd[2];
	pid_t	pids[2];
	int		status;

	pipe(fd);
	pids[0] = first_child(cmd, fd);
	pids[1] = second_child(cmd->next, fd);
	close(fd[0]);
	close(fd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pids[0], NULL, 0);
	waitpid(pids[1], &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = WTERMSIG(status) + 128;
	return (0);
}
