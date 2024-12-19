/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 10:19:38 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/15 21:12:42 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

// +---------------------+
// |                     |  <-- Buffer Pointer (buffer)
// |                     |
// |                     |  <-- Memory Location (size bytes)
// |                     |
// |                     |
// |                     |   <-- Representation of the buffer in memory
// |                     |
// |                     |
// |      "/home/user/"  |   <-- Example content of the buffer
// |                     |
// |                     |
// |                     |
// |                     |
// |      '\0'          |   <-- NUL-termination (marks end of the string)
// |                     |
// +---------------------+

int	pwd_builtin(t_cmd *cmd)
{
	char	*cwd;

	cwd = NULL;
	(void)cmd;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		cwd = get_env(shell.envholder, "PWD");
		if (!cwd)
		{
			perror("pwd: error retrieving current directory");
			return (1);
		}
		printf("%s\n", cwd);
	}
	else
	{
		printf("%s\n", cwd);
		update_env(&(shell.envholder), "PWD", cwd);
		free(cwd);
	}
	return (0);
}
