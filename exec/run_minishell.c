/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:08:32 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/05 14:53:34 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

void	check_command_access(char **paths, char **command, t_shell *shell)
{
	int		i;
	char	*mid_path;
	char	*full_path;
	char	**args;
    
	i = 0;
	while (paths[i] != NULL)
	{
		mid_path = ft_strjoin(paths[i], "/");
		if (mid_path == NULL)
		{
			i++;
			continue ;
		}
		full_path = ft_strjoin(mid_path, command[0]);
		free(mid_path);
		if (full_path == NULL)
		{
			i++;
			continue ;
		}
		if (access(full_path, X_OK) == 0)
		{
			args = parse_and_handle_redirection(shell);
			if (execve(full_path, args, shell->envholder) == -1)
			{
				perror("execv failed");
				free(full_path);
				exit(EXIT_FAILURE);
			}
		}
		free(full_path);
		i++;
	}
	ft_putstr_fd("Command not found: ", 2);
	ft_putstr_fd(command[0], 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

int	count_commands_anf_flags(t_shell *shell)
{
	int	i;
	int	arg_count;

	arg_count = 0;
	i = 0;
	while (shell->cmd->args[i] != NULL)
	{
		if (strcmp(shell->cmd->args[i], "<") != 0 && strcmp(shell->cmd->args[i],
				"<<") != 0 && strcmp(shell->cmd->args[i], ">") != 0
			&& strcmp(shell->cmd->args[i], ">>") != 0 && (i == 0
				|| (strcmp(shell->cmd->args[i - 1], "<") != 0
					&& strcmp(shell->cmd->args[i - 1], "<<") != 0
					&& strcmp(shell->cmd->args[i - 1], ">") != 0
					&& strcmp(shell->cmd->args[i - 1], ">>") != 0)))
		{
			arg_count++;
		}
		i++;
	}
	return (arg_count);
}

char	**copy_command_and_flags(t_shell *shell, char **only_args)
{
	int	arg_index;
	int	i;

	arg_index = 0;
	i = 0;
	only_args[arg_index++] = strdup(shell->cmd->order);
	while (shell->cmd->args[i] != NULL)
	{
		if (strcmp(shell->cmd->args[i], "<") != 0 && strcmp(shell->cmd->args[i],
				"<<") != 0 && strcmp(shell->cmd->args[i], ">") != 0
			&& strcmp(shell->cmd->args[i], ">>") != 0 && (i == 0
				|| (strcmp(shell->cmd->args[i - 1], "<") != 0
					&& strcmp(shell->cmd->args[i - 1], "<<") != 0
					&& strcmp(shell->cmd->args[i - 1], ">") != 0
					&& strcmp(shell->cmd->args[i - 1], ">>") != 0)))
		{
			only_args[arg_index++] = strdup(shell->cmd->args[i]);
		}
		i++;
	}
	only_args[arg_index] = NULL;
	return (only_args);
}

char	**parse_and_handle_redirection(t_shell *shell)
{
	int		arg_count;
	char	**only_args;

	arg_count = count_commands_anf_flags(shell);
	only_args = malloc(sizeof(char *) * (arg_count + 1));
	only_args = copy_command_and_flags(shell, only_args);
	return (only_args);
}

void	run_simplecmd(t_shell *shell, t_envvar *envp, char **av)
{
	char	*path_str;
	char	**paths;

	path_str = find_path(envp);
	if (path_str == NULL)
	{
		printf("PATH Not Found\n");
		return ;
	}
	paths = split_path(path_str);
	if (paths == NULL)
	{
		printf("Failed to split the path\n");
		return ;
	}
	check_command_access(paths, av, shell);
}

// char    **split_path(char *path_string)
// {
//     //TODO replace strtok (strtok is not allowed);
//     int     counter;
//     char    *temp;
//     char    **paths;
//     char    *path_copy;
//     int     index;
//     char    *current;

//     counter = 1;
//     temp = path_string;
//     while(*temp)
//     {
//         if (*temp == ':')
//             counter++;
//         temp++;
//     }
//     paths = malloc(sizeof(char *) * (counter + 1));
//     if (paths == NULL)
//         return(NULL);
//     path_copy = strdup(path_string);
//     if (path_copy == NULL)
//     {
//         free(paths);
//         return(NULL);
//     }
//     index = 0;
//     current = ft_strtok(path_copy, ':');
//     while(current != NULL)
//     {
//         paths[index] = strdup(current);
//         if (paths[index] == NULL)
//         {
//             while(index > 0)
//             {
//                 index--;
//                 free(paths[index]);
//             }
//             free(paths);
//             free(path_copy);
//             return(NULL);
//         }
//         index++;
//         current = ft_strtok(NULL, ':');
//     }
//     paths[index] = NULL;
//     free(path_copy);
//     return(paths);
// }