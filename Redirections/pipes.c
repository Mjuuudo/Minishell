/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 09:34:06 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/03 15:49:37 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

// TODO FIX THE INPUT CAT | LS -L

void	close_pipes(int *pipes_array, int count)
{
	int	j;

	j = 0;
	while (j < 2 * (count - 1))
	{
		close(pipes_array[j]);
		j++;
	}
} 
/*
!=======================Execute Commands=====================!
 This function forks a process for each command in the `t_cmd` linked list.
 Each child process executes a single command,
	while the parent continues iterating.
 It uses `execute_single_command` to handle redirections and command execution.
 The parent restores the original `shell->cmd` after all commands are forked.
*/

void	execute_commands(t_shell *shell, t_cmd *current, int *pipes_array,
		int count)
{
	int		i;
	t_cmd	*cmd_ptr;
	pid_t	pid;

	i = 0;
	cmd_ptr = current;
	while (cmd_ptr != NULL)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork failed");
			return ;
		}
		if (pid == 0)
		{
			shell->cmd = cmd_ptr;
			// printf("[%d]: shell->cmd->order is %s\n", i, shell->cmd->order);
			execute_single_command(shell, pipes_array, i, count);
		}
		i++;
		cmd_ptr = cmd_ptr->next;
	}
	shell->cmd = current;
}

void	create_pipe_array(int count, int *pipes_array)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pipe(pipes_array + i * 2) == -1)
			return ;
		i++;
	}
}

int	count_commands(t_cmd *current)
{
	int	counter;

	counter = 0;
	while (current != NULL)
	{
		counter++;
		current = current->next;
	}
	return (counter);
}
/*
!!=====================Handle Pipes=====================!
 This function orchestrates the piping and 
 execution process for a set of commands.
 1. Counts the number of commands in the `t_cmd` linked list.
 2. Handles the special case of a single command without pipes.
 3. Allocates memory for the `pipes_array` and 
 initializes it using `create_pipe_array`.
 4. Executes all commands using `execute_commands`,
	then closes pipes and waits for all children.
 If memory allocation fails or a command list is empty,
	the function returns early.
*/

void	handle_pipes(t_shell *shell)
{
	t_cmd	*current;
	int		count;
	int		*pipes_array;
	pid_t	pid;

	if (shell->cmd == NULL)
		return ;
	current = shell->cmd;
	count = count_commands(current);
	if (count == 1)
	{
		printf("count is 1\n");
		pid = fork();
		if (pid == 0)
			(execute_command(shell, current->order), exit(EXIT_FAILURE));
		wait(NULL);
		return ;
	}
	pipes_array = malloc(sizeof(int) * 2 * (count - 1));
	if (pipes_array == NULL)
		return ;
	create_pipe_array(count - 1, pipes_array);
	execute_commands(shell, current, pipes_array, count);
	close_pipes(pipes_array, count);
	wait_for_children(count);
	free(pipes_array);
}
