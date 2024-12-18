/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:50:34 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/18 23:37:31 by oer-refa         ###   ########.fr       */
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

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
void cleanup_temp_files(void)
{
    if (shell.temp_file)
    {
        unlink(shell.temp_file); // Remove the temporary file
        free(shell.temp_file);
        shell.temp_file = NULL;
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
		if (!*line)
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
			// implement_heredoc(shell->cmd, shell->envp);
			// ft_execution(shell->cmd);
			if (implement_heredoc(shell->cmd,shell->envp) == 0)
			{
				ft_execution(shell->cmd);
				cleanup_temp_files();
			}
			ft_freecmdmain(shell);
		}
    }
	// ft_freecmdmain(shell);
    printf("Exiting Shell ...\n");
    free(line);
}

int set_files(t_cmd *cmd) {
    char template[] = "mont_XXXXXX"; // Template for mkstemp
    int fd = mkstemp(template);
    if (fd == -1) {
        perror("minishell: Failed to create temporary file");
        return -1;
    }
    shell.temp_file = strdup(template); // Store the file name
    return fd;
}



// int set_files2(t_cmd *cmd, int index)
// {
// 	char *file_name;
// 	char *num;
// 	int fd;

// 	file_name = ft_strdup("lo");
// 	num = ft_itoa(index);
// 	shell.temp_file = ft_strjoin(file_name, num);
// 	printf("shell.temp_file = %s\n", shell.temp_file);
// 	fd = open(shell.temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	free(file_name);
// 	free(num);
// 	close(fd);
// 	return (fd);
// }

void heredoc_sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		exit(120);
	}
}



bool	execute_builtin(t_cmd *cmd)
{
	int			i;
	static char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	static int	(*builtin_functions[])(t_cmd *) = {echo_builtin, cd_builtin,
		pwd_builtin, export_builtin, unset_builtin, env_builtin, exit_builtin};

	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(cmd->order, builtins[i]) == 0)
		{
			if (!set_redirections(cmd->red))
				return (reset_redirections(), false);
			builtin_functions[i](cmd);
			reset_redirections();
			return (true);
		}
		i++;
	}
	return (false);
}

int	execute_without_path(t_cmd *cmd)
{
	char **args;
	int i = 0;

	args = parse_and_handle_redirection(&shell);
	join_order_with_args(cmd, args);
	execve(cmd->order, args, shell.envholder);
	perror("minishell033$");
	exit(1);
}

char *get_full_path2(char **paths, t_cmd *cmd)
{
	int		i;
	char	*full_path = NULL;
	char	*temp = NULL;

	i = 0;
	while (paths[i])
	{
		temp = join_path(paths[i], cmd->order);
		if (temp == NULL)
			return (NULL);
		if (access(temp, X_OK) == 0)
			return (temp);
		free(temp);
		i++;
	}
	return (NULL);
}

char 	*making_the_path(t_cmd *cmd)
{
	char *path_str = NULL;
	char **paths = NULL;
	char *full_path = NULL;
	int i = 0;

	path_str = find_path(shell.envp);
	if (path_str == NULL)
	{
		printf("PATH Not Found\n");
		return (NULL);
	}
	paths = split_path(path_str);
	if (paths == NULL)
		return (NULL);
	full_path = get_full_path2(paths, cmd);
	while(paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	return (full_path);
}

void	join_order_with_args(t_cmd *cmd, char **args)
{
	int	i;

	i = 0;
	args[0] = cmd->order;
	while (cmd->args[i])
	{
		args[i + 1] = cmd->args[i];
		i++;
	}
	// args[i + 1] = NULL;
}

int	execute_with_path(t_cmd *cmd)
{
	char	*path = NULL;
	char *test_path;
	char	**args = NULL;
	int 	i = 0;

	path = making_the_path(cmd);
	if (path == NULL)
	{
		fprintf(stderr, "minishell04$: command not found: %s\n", cmd->order);
		free(path);
		exit(127);
	}

	args = parse_and_handle_redirection(&shell);
	join_order_with_args(cmd, args);
	// int j = 0;
	// while(j)
	// {
	// 	printf("args[%d] = %s\n", j, args[j]);
	// 	j++;
	// }
	// test_path = "/bin/wc";
	if (execve(path, args , shell.envholder) == -1)
	{
		perror("minishell05$");
    	while(args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
		free(path);
		exit(1);
	}
	exit(1);
}



int ft_execute(t_cmd *cmd)
{
	if (!execute_builtin(cmd))
		execute_cmd(cmd);
	return (0);
}

int	first_child(t_cmd *cmd, int *fd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute_cmd(cmd);
		// ft_freeenv(shell.envp);
		// ft_freeenvholder(shell.envholder);
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
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		ft_execution(cmd);
		// ft_freeenv(shell.envp);
		// ft_freeenvholder(shell.envholder);
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

int ft_execution(t_cmd *cmd)
{
	if (cmd->next)
	{
		execute_pipe(cmd);
	}
	else
	{
		ft_execute(cmd);
	}
	return (0);
}
