/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:08:41 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/07 21:54:14 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

void	wait_for_children(int count)
{
	int	j;

	j = 0;
	while (j < count)
	{
		wait(NULL);
		j++;
	}
}

void	close_unused_pipes(int *pipes_array, int count, int i)
{
	int	j;

	j = 0;
	while (j < 2 * (count - 1))
	{
		if (j != 2 * (i - 1) && j != 2 * i + 1)
			close(pipes_array[j]);
		j++;
	}
}

void	setup_redirection(int *pipes_array, int i, int direction)
{
	if (direction == STDIN_FILENO)
		dup2(pipes_array[2 * (i - 1)], STDIN_FILENO);
	else if (direction == STDOUT_FILENO)
		dup2(pipes_array[2 * i + 1], STDOUT_FILENO);
}

void	execute_single_command(t_shell *shell, int *pipes_array, int i,
		int count)
{
	// printf("in setup before shell->cmd->order: %s\n", shell->cmd->order);

	if (i == 0 && count > 1)
	{
		dup2(pipes_array[1], STDOUT_FILENO);
		close_unused_pipes(pipes_array, count, i);
	}
	else if (i < count - 1)
	{
		setup_redirection(pipes_array, i, STDIN_FILENO);
		setup_redirection(pipes_array, i, STDOUT_FILENO);
		close_unused_pipes(pipes_array, count, i);
	}
	else if (i == count - 1)
	{
		setup_redirection(pipes_array, i, STDIN_FILENO);
		close_unused_pipes(pipes_array, count, i);
	}
	// printf("in setup after shell->cmd->order: %s\n", shell->cmd->order);
	// check_if_builtin(shell);
	// execute_command(shell, shell->cmd->order);
	exit(EXIT_FAILURE);
}


//!=======================execute_single_command=====================!
//  Executes a single command in the pipeline by setting up proper redirections.
//  Handles input and output redirections based
//  on the command's position in the pipeline.
//  The function exits the process after execution of the command.
//  For the first command in the pipeline,
//  output is redirected to the write-end of the first pipe.
//  This ensures data flows correctly to the next command.
//  For intermediate commands,
//  both input and output are redirected to appropriate pipe ends.
//  This ensures they read from the previous command and write to the next.
//  For the last command,
//	input is redirected from the read-end of the previous pipe.
//  No output redirection is needed as it writes directly to standard output.
//  Unused pipes are closed to prevent resource leaks during
//  the execution of the pipeline.
//  The function calls `execute_command` to run the specified shell command.
//  If `execute_command` fails, the process exits with a failure code.
