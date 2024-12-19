/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 08:19:40 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/19 10:13:37 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

static void	execute_command(t_cmd *cmd)
{
	if (!set_redirections(cmd->red))
		exit(1);
	if (!execute_builtin(cmd))
	{
		if (ft_strchr('/', cmd->order))
			execute_without_path(cmd);
		else
			execute_with_path(cmd);
	}
	exit(0);
}

int	execute_cmd(t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		setup_child_signals();
		execute_command(cmd);
	}
	else if (pid > 0)
		handle_parent_process(pid);
	else
		perror("Fork failed");
	return (shell.exit);
}

int	ft_execute(t_cmd *cmd)
{
	if (!execute_builtin(cmd))
		execute_cmd(cmd);
	return (0);
}

int	ft_execution(t_cmd *cmd)
{
	if (cmd->next)
		execute_pipe(cmd);
	else
		ft_execute(cmd);
	return (0);
}
