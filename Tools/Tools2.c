/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:02:15 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/19 10:26:06 by oer-refa         ###   ########.fr       */
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
