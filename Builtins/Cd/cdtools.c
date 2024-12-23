/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdtools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 23:51:38 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/22 23:53:56 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	path_from_shell_env(t_cmd *cmd, char **path)
{
	*path = get_env(shell.envholder, "HOME");
	if (!*path)
	{
		perror("cd: HOME not set");
		shell.exit = 1;
		return (1);
	}
	return (0);
}

void	print_it_norm(char *path)
{
	perror("cd");
	perror("");
	shell.exit = 1;
}

void	print_it_norm2(char *path)
{
	printf("cd: %s: error retrieving current directory\n", path);
	shell.exit = 1;
}
