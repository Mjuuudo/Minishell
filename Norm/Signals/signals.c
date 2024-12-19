/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:11:18 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/19 10:23:13 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handle_signal_termination(int status)
{
	if (WTERMSIG(status) == SIGQUIT)
		printf("Quit (core dumped)\n");
	else if (WTERMSIG(status) == SIGINT)
		printf("\n");
}

void	setup_parent_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	restore_parent_signals(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_parent_process(pid_t pid)
{
	int	status;

	setup_parent_signals();
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell.exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell.exit = WTERMSIG(status) + 128;
	if (WIFSIGNALED(status))
		handle_signal_termination(status);
	restore_parent_signals();
}
