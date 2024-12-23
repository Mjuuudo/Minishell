/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 10:19:38 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/23 01:38:13 by oer-refa         ###   ########.fr       */
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

size_t	ft_str_lcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] != '\0' && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*join2(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*ptr;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = ft_malloc(sizeof(char) * (len1 + len2 + 1), 'm');
	if (!ptr)
		return (NULL);
	strcpy(ptr, s1);
	strcat(ptr, s2);
	return (ptr);
}

void	get_logical_pwd(char **env, char *old_pwd)
{
	char	*logical_pwd;

	logical_pwd = get_env(shell.envholder, "PWD");
	if (logical_pwd)
		ft_strncpy(old_pwd, logical_pwd, sizeof(old_pwd) - 1);
	else
		old_pwd[0] = '\0';
}
