/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 10:19:38 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/02 09:50:32 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../Includes/Minishell.h"



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


void	ft_putstr(char *str)
{
	while (*str != '\0')
	{
		write(1, str, 1);
		str++;
	}
}

//char* getcwd( char* buffer, size_t size );

int	pwd_builtin(t_cmd *cmd)
{
	// char *buffer[PATH_MAX];
	char *cwd;
	
	(void)cmd;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		ft_putstr("Error: Could not get the current working directory");
		return (1);
	}
	write(1, cwd, strlen(cwd));
	write(1, "\n", 1);
	free(cwd);
	return (0);
}