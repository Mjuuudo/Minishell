/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:02:15 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/16 23:44:55 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (fd < 0)
		return ;
	while (s && s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

char	*ft_strtok(char *string, char c)
{
	static char	*last_pos = NULL;
	char		*start;

	if (string != NULL)
		last_pos = string;
	else if (last_pos == NULL)
		return (NULL);
	while (*last_pos == c)
		last_pos++;
	if (*last_pos == '\0')
		return (NULL);
	start = last_pos;
	while (*last_pos != '\0' && *last_pos != c)
		last_pos++;
	if (*last_pos != '\0')
	{
		*last_pos = '\0';
		last_pos++;
	}
	return (start);
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

char	**split_path(char *path_string)
{
	int		counter;
	char	*temp = NULL;
	char	**paths = NULL;
	char	*path_copy = NULL;

	counter = 0;
	temp = path_string;
	counter = counte_temp(temp);
	// printf("couter = %d\n", counter);
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

char	**split_path3(char **paths, char *path_copy)
{
	int		index;
	char	*current = NULL;

	index = 0;
	current = ft_strtok(path_copy, ':');
	while (current != NULL)
	{
		paths[index] = strdup(current);
		if (paths[index] == NULL)
		{
			while (index > 0)
			{
				index--;
				free(paths[index]);
			}
			free(paths);
			free(path_copy);
		}
		index++;
		current = ft_strtok(NULL, ':');
	}
	paths[index] = NULL;
	index = 0;
	free(path_copy);
	return (paths);
}

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
