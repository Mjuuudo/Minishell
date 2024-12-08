/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 00:24:09 by oer-refa          #+#    #+#             */
/*   Updated: 2024/11/28 10:39:51 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

// int execute_redirections(t_shell *shell)
// {
//     t_redirection *current;
//     int saved_stdin;
//     int saved_stdout;
//     pid_t pid;
//     int status;

//     current = shell->cmd->red;
//     saved_stdin = dup(STDIN_FILENO);
//     saved_stdout = dup (STDOUT_FILENO);

//     if (saved_stdin == -1 || saved_stdout == -1)
//     {
//         perror("Failed to save standard file descriptors");
//         return (-1);
//     }
//     pid = fork();
//     if (pid == -1)
//     {
//         perror("fork failed");
//         restore_fds(saved_stdin, saved_stdout);
//         return (-1);
//     }
//     if (pid == 0)
//     {
//         while(current)
//         {
//             if (handle_single_redirections(current) == -1)
//                 exit(EXIT_FAILURE);
//             current = current->next;
//         }
//         execute_command(shell, shell->cmd->order);
//         exit(EXIT_FAILURE);
//     }
//     else
//         waitpid(pid, &status, 0);
//     restore_fds(saved_stdin, saved_stdout);
// }
/*
 ! handle_single_redirections:
  Handles a single redirection by opening the specified file and setting up 
  the correct file descriptor redirection for input or output. 
  Returns 0 on success, or -1 on failure.
 */

int	handle_single_redirections(t_redirection *current)
{
	int	fd;

	fd = handle_single_redirections2(current);
	if (fd == -1)
		return (fd);
	if ((current->identifier == GREAT || current->identifier == DGREAT)
		&& dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Failed to redirect STDOUT");
		close(fd);
		return (-1);
	}
	else if (current->identifier == LESS && dup2(fd, STDIN_FILENO) == -1)
	{
		perror("Failed to redirect STDIN");
		close(fd);
		return (-1);
	}
	if (close(fd) == -1)
	{
		perror("Failed to close file descriptor");
		return (-1);
	}
	return (0);
}

/*
 ! child_handle_redirections:
  Handles redirections in a child process. Iterates over all redirections,
  applying each, and then executes the command. Exits the process on failure.
 */

static int	child_handle_redirections(t_shell *shell)
{
	t_redirection	*current;

	current = shell->cmd->red;
	while (current)
	{
		if (handle_single_redirections(current) == -1)
			exit(EXIT_FAILURE);
		current = current->next;
	}
	execute_command(shell, shell->cmd->order);
	exit(EXIT_FAILURE);
}

/*
 ! restore_fds:
  Restores the saved standard input and output file descriptors, closing 
  the saved descriptors after restoring. Ensures the shell's standard I/O 
  streams are reset to their original state.
 */

void	restore_fds(int saved_stdin, int saved_stdout)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

/*
 ! prepare_redirections:
  Saves the current standard input and output file descriptors for later 
  restoration. Returns 0 on success, or -1 if saving fails.
 */

static int	prepare_redirections(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdin == -1 || *saved_stdout == -1)
	{
		perror("Failed to save standard file descriptors");
		return (-1);
	}
	return (0);
}
/*
 ! ===========================execute_redirections=======================
 ? Executes all redirections in a child process, then executes the command. 
 ? Uses `prepare_redirections` to save the standard file descriptors and 
 ? `restore_fds` to restore them after the child process finishes.
 ? Waits for the child process to complete and returns its exit status.
 */

int	execute_redirections(t_shell *shell)
{
	int		saved_stdin;
	int		saved_stdout;
	pid_t	pid;
	int		status;

	if (prepare_redirections(&saved_stdin, &saved_stdout) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		restore_fds(saved_stdin, saved_stdout);
		return (-1);
	}
	if (pid == 0)
		child_handle_redirections(shell);
	waitpid(pid, &status, 0);
	restore_fds(saved_stdin, saved_stdout);
	return (WEXITSTATUS(status));
}
