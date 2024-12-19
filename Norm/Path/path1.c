/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:38:04 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/19 10:09:54 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

int	counte_temp(char *temp)
{
	int	counter;

	counter = 1;
	while (*temp)
	{
		if (*temp == ':')
			counter++;
		temp++;
	}
	return (counter);
}

char	**split_path(char *path_string)
{
	int		counter;
	char	*temp;
	char	**paths;
	char	*path_copy;

	counter = 1;
	temp = path_string;
	counter = counte_temp(temp);
	paths = malloc(sizeof(char *) * (counter + 1));
	if (paths == NULL)
		return (NULL);
	path_copy = strdup(path_string);
	if (path_copy == NULL)
	{
		free(paths);
		return (NULL);
	}
	paths = split_path3(paths, path_copy);
	return (paths);
}

char	*find_path(t_envvar *envp)
{
	while (envp != NULL)
	{
		if (strcmp(envp->key, "PATH") == 0)
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

char	*making_the_path(t_cmd *cmd)
{
	char	*path_str;
	char	**paths;

	path_str = find_path(shell.envp);
	if (path_str == NULL)
	{
		printf("PATH Not Found\n");
		return (NULL);
	}
	paths = split_path(path_str);
	return (get_full_path2(paths, cmd));
}
