/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:09:57 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/22 22:44:18 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

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
}

char	*join_path(const char *base, const char *command)
{
	char	*mid_path;
	char	*full_path;

	mid_path = NULL;
	full_path = NULL;
	mid_path = ft_strjoin(base, "/");
	if (!mid_path)
		return (NULL);
	full_path = ft_strjoin(mid_path, command);
	return (full_path);
}

char	*get_full_path(char **paths, t_cmd *cmd)
{
	char	*full_path;
	int		i;

	full_path = NULL;
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

char	*get_full_path2(char **paths, t_cmd *cmd)
{
	int		i;
	char	*temp;

	temp = NULL;
	i = 0;
	while (paths[i])
	{
		temp = join_path(paths[i], cmd->order);
		if (temp == NULL)
			return (NULL);
		if (access(temp, X_OK) == 0)
		{
			return (temp);
		}
		i++;
	}
	return (NULL);
}

char	**split_path3(char **paths, char *path_copy)
{
	int		index;
	char	*current;

	current = NULL;
	index = 0;
	current = ft_strtok(path_copy, ':');
	while (current != NULL)
	{
		paths[index] = ft_strdup(current);
		if (paths[index] == NULL)
		{
			while (index > 0)
			{
				index--;
			}
		}
		index++;
		current = ft_strtok(NULL, ':');
	}
	paths[index] = NULL;
	return (paths);
}
