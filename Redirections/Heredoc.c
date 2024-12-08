/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:34:51 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/07 12:49:50 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

int count_heredoc(t_cmd *current)
{
    int heredoc_counter = 0;

    while (current)
    {
        t_redirection *temp = current->red;
        while (temp)
        {
            if (temp->identifier == 5) 
                heredoc_counter++;
            temp = temp->next;
        }
        current = current->next;
    }
    return heredoc_counter;
}

void heredoc_inplementation_0(int heredoc_counter, t_cmd *current,
                              t_shell *shell, char **heredoc_files)
{
    int i = 0;
    char *filename, *num, *temp_file;
    t_redirection *temp;

    while (current)
    {
        temp = current->red;
        while (temp)
        {
            if (temp->identifier == 5)
            {
                filename = ft_strdup("mont_");
                num = ft_itoa(i);
                temp_file = ft_strjoin(filename, num);
                free(filename);
                free(num);

                heredoc_files[i] = temp_file;
                process_heredoc_input(temp->file, temp_file);
                i++;
            }
            temp = temp->next;
        }

        if (i > 0)
        {
            execute_command_with_multiple_heredocs(heredoc_files, i, current->order,
                                                   shell->envp, shell);
            i = 0;
        }

        current = current->next;
    }
}

void execute_command_with_multiple_heredocs(char **heredoc_files, int count,
                                            char *cmd, t_envvar *envp, t_shell *shell)
{
    int input_fd, temp_fd, i;
    pid_t pid;
    int status;


    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("Failed to create pipe for heredocs");
        exit(1);
    }

    for (i = 0; i < count; i++)
    {
        temp_fd = open(heredoc_files[i], O_RDONLY);
        if (temp_fd < 0)
        {
            perror("Failed to open heredoc temp file");
            exit(1);
        }
        char buffer[1024];
        ssize_t bytes;
        while ((bytes = read(temp_fd, buffer, sizeof(buffer))) > 0)
            write(pipefd[1], buffer, bytes);

        close(temp_fd);
    }
    close(pipefd[1]);

    pid = fork();
    if (pid == 0)
    {
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        run_simplecmd(shell, envp, &cmd);
        exit(0);
    }
    else if (pid > 0)
    {
        close(pipefd[0]);
        waitpid(pid, &status, 0);
    }
    else
    {
        perror("Fork failed");
    }
}



void	heredoc_inplementation(int heredoc_counter, t_cmd *current,
		t_shell *shell, char **heredoc_files)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		heredoc_inplementation_0(heredoc_counter, current, shell,
			heredoc_files);
		return ;
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return ;
	}
	else
	{
		perror("Fork failed");
	}
}

bool	check_heredoc(t_shell *shell)
{
	t_cmd			*current;
	char			**heredoc_files;
	int				heredoc_counter;

	heredoc_counter = 0;
	if (!shell || !shell->cmd || !shell->cmd->red)
		return (false);
	current = shell->cmd;
	heredoc_counter = count_heredoc(current);
	printf("heredoc_counter %d\n", heredoc_counter);
	if (heredoc_counter == 0)
		return (false);
	heredoc_files = NULL;
	heredoc_files = malloc(sizeof(char *) * heredoc_counter);
	if (!heredoc_files)
		return (false);
	current = shell->cmd;
	heredoc_inplementation(heredoc_counter, current, shell, heredoc_files);
	return (true);
}

int	handle_heredoc(t_shell *shell)
{
	if (!shell)
		return (1);
	if (!check_heredoc(shell))
	{
		printf("heredoc not found\n");
		execute_command(shell, shell->cmd->order);
	}
	return (2);
}
