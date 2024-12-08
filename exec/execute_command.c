/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:38:04 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/02 12:20:31 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

void	execute_command(t_shell *shell, char *order)
{
	char	*path_str;
	char	**paths;
	t_cmd	*original_cmd;
	t_cmd	temp_cmd;

	path_str = NULL;
	original_cmd = shell->cmd;
	path_str = find_path(shell->envp);
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
	temp_cmd = *shell->cmd;
	temp_cmd.order = order;
	shell->cmd = &temp_cmd;
	check_command_access2(paths, shell, &temp_cmd);
	shell->cmd = original_cmd;
}

char	*join_path(const char *base, const char *command)
{
	char	*mid_path;
	char	*full_path;

	mid_path = ft_strjoin(base, "/");
	if (!mid_path)
		return (NULL);
	full_path = ft_strjoin(mid_path, command);
	free(mid_path);
	return (full_path);
}

char	*get_full_path(char **paths, t_cmd *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i] != NULL)
	{
		full_path = join_path(paths[i], cmd->order);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}

void	check_command_access2(char **paths, t_shell *shell, t_cmd *cmd)
{
	char	*full_path;
	char	**args;

	full_path = get_full_path(paths, cmd);
	if (full_path == NULL)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(shell->cmd->order, 2);
		ft_putstr_fd("\n", 2);
		exit(EXIT_FAILURE);
	}
	args = parse_and_handle_redirection(shell);
	if (execve(full_path, args, shell->envholder) == -1)
	{
		perror("execv failed");
		free(full_path);
		exit(EXIT_FAILURE);
	}
	free(full_path);
}
