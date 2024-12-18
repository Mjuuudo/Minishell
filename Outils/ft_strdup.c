/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:58:32 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/18 15:29:45 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

char	*ft_strdup(const char *str)
{
	int		i;
	int		len_str;
	char	*strcp;

	len_str = ft_strlen(str);
	strcp = (char *)malloc(len_str + 1);
	if (!strcp)
		return (NULL);
	i = 0;
	while (str[i])
	{
		strcp[i] = str[i];
		i++;
	}
	strcp[i] = '\0';
	return (strcp);
}
