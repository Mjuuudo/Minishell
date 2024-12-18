/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part_01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:14:30 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/18 14:12:10 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

static int	quote_or_not(char *line)
{
	int	counter;

	counter = 0;
	while (line[counter])
	{
		if (line[counter] == '"' || line[counter] == 39)
			return (1);
		counter++;
	}
	return (0);
}

static char	*removequotes(char *line, int i, int flag, int counter)
{
	char	*new_str;
	char	sym;

	new_str = malloc(sizeof(char) * (ft_strlen(line) * 2 + 1));
	if (!new_str)
		return (NULL);
	while (line[counter])
	{
		if ((line[counter] == '"' || line[counter] == 39) && flag == 0)
		{
			flag = 1;
			sym = line[counter];
			counter++;
		}
		else if (sym == line[counter] && flag == 1)
		{
			flag = 0;
			sym = 0;
			counter++;
		}
		else
			new_str[i++] = line[counter++];
	}
	new_str[i] = '\0';
	return (new_str);
}

void	ft_quotesremove(t_cmd **node)
{
	int		counter;
	char	*new;

	counter = 0;
	if (quote_or_not((*node)->order))
	{
		new = removequotes((*node)->order, 0, 0, 0);
		free((*node)->order);
		(*node)->order = ft_strdup(new);
		free(new);
	}
	while ((*node)->args[counter])
	{
		if (quote_or_not((*node)->args[counter]))
		{
			new = removequotes((*node)->args[counter], 0, 0, 0);
			free((*node)->args[counter]);
			(*node)->args[counter] = ft_strdup(new);
			free(new);
		}
		counter++;
	}
}
