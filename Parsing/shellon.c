/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:50:34 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/20 12:09:28 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"
#define PATH_MAX 1024

int ft_quotes(char *line, int index)
{
    int counter;
    char sym;
    int start;
    int end;

    counter = 0;
    while (line[counter])
    {
        if (line[counter] == 39 || line[counter] == '"')
        {
            start = counter;
            sym = line[counter++];
            while(line[counter] != sym && line[counter])
                counter++;
            end = counter;
             if (start <= index && end >= index)
                return (1);
        }
        counter++;
    }
    return (0);
}

static void display_cmd(t_shell *shell)
{
    int i = 0;
    while (shell->cmd)
    {
        printf("arg cmd [ ] %s\n", shell->cmd->order);
        while (shell->cmd->args[i])
        {
                printf("-->  args [%d] %s\n", i, shell->cmd->args[i]);
                i++;
        }
        i = 0;
		while (shell->cmd->red2[i])
        {
                printf("-->  redirection in red 2 [%d] %s\n", i, shell->cmd->red2[i]);
                i++;
        }
		i = 0;
        printf("---------- Redirections -------------\n");
        while (shell->cmd->red)
        {

            printf ("File %s, Type %d\n", shell->cmd->red->file, shell->cmd->red->identifier);
            shell->cmd->red = shell->cmd->red->next;
        }
        printf("------------ End Redirection -----------\n");
        shell->cmd = shell->cmd->next;
    }
}


void ft_shell_on(t_shell *shell)
{
	char *line;
	int i = 0;
	signal(SIGQUIT, SIG_IGN);
	while (true)
	{
		signal(SIGINT, handler);
		line = readline("Blackhole_Lover's@Minis(hell):~$ ");
		signal(SIGINT, SIG_IGN);
		if (!line)
			break ;
		if (!*line || ft_videornor(line))
		{
			free(line);
			continue ;
		}
		add_history(line);
			if (ft_quotesch(line, shell) && ft_pipe(line, shell)
		&& ft_redirections(line, shell))
		{
			ft_cmdhandler(line, shell);
			// display_cmd(shell);
			// if counter dyal l heredoc > 0

			implement_heredoc(shell->cmd);
			ft_execution(shell->cmd);
		}
		ft_freecmdmain(shell);
	}
	printf("exit\n");
	free(line);
}

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

// void	reset_redirections(void)
// {
// 	int	fd;

// 	fd = open("/dev/tty", O_RDWR);
// 	dup2(fd, STDIN_FILENO);
// 	dup2(fd, STDOUT_FILENO);
// 	close(fd);
// }


// char *get_full_path2(char **paths, t_cmd *cmd)
// {
// 	int		i;
// 	char	*full_path;
// 	char	*temp;

// 	i = 0;
// 	while (paths[i])
// 	{
// 		temp = join_path(paths[i], cmd->order);
// 		if (temp == NULL)
// 			return (NULL);
// 		if (access(temp, X_OK) == 0)
// 		{
// 			return (temp);
// 		}
// 		free(temp);
// 		i++;
// 	}
// 	return (NULL);
// }

// char 	*making_the_path(t_cmd *cmd)
// {
// 	char *path_str;
// 	char **paths;

// 	path_str = find_path(shell.envp);
// 	if (path_str == NULL)
// 	{
// 		printf("PATH Not Found\n");
// 		return (NULL);
// 	}
// 	paths = split_path(path_str);
// 	return (get_full_path2(paths, cmd));
// }

// void	join_order_with_args(t_cmd *cmd, char **args)
// {
// 	int	i;

// 	i = 0;
// 	args[0] = cmd->order;
// 	while (cmd->args[i])
// 	{
// 		args[i + 1] = cmd->args[i];
// 		i++;
// 	}
// 	args[i + 1] = NULL;
// }

// int	first_child(t_cmd *cmd, int *fd)
// {
// 	int	pid;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[1]);
// 		execute_cmd(cmd);
// 		exit(1);
// 	}
// 	return (pid);
// }

// int	second_child(t_cmd *cmd, int *fd)
// {
// 	int	pid;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 		ft_execution(cmd);
// 		exit(1);
// 	}
// 	return (pid);
// }

// int	execute_pipe(t_cmd *cmd)
// {
// 	int		fd[2];
// 	pid_t	pids[2];
// 	int		status;

// 	pipe(fd);
// 	pids[0] = first_child(cmd, fd);
// 	pids[1] = second_child(cmd->next, fd);
// 	close(fd[0]);
// 	close(fd[1]);
// 	signal(SIGINT, SIG_IGN);
// 	waitpid(pids[0], NULL, 0);
// 	waitpid(pids[1], &status, 0);
// 	if (WIFEXITED(status))
// 		status = WEXITSTATUS(status);
// 	else if (WIFSIGNALED(status))
// 		status = WTERMSIG(status) + 128;
// 	return (0);
// }
