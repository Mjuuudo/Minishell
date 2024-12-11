/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:38:04 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/11 09:53:15 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

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

