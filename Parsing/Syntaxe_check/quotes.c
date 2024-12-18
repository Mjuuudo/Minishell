/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:25:48 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/18 11:36:03 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

static int	check_double(char *line)
{
	int		counter;
	int		quotes;
	char	sym;

	counter = 0;
	quotes = 0;
	while (line[counter])
	{
		quotes = 0;
		if ((line[counter] == '"' || line[counter] == 39))
		{
			quotes = 1;
			sym = line[counter++];
			while (line[counter] != sym && line[counter])
				counter++;
			if (line[counter] == sym)
				quotes = 0;
			if (quotes == 1)
				return (0);
		}
		counter++;
	}
	return (1);
}

int	ft_quotesch(char *line, t_shell *shell)
{
	(void)shell;
	if (!check_double(line))
	{
		printf("Syntaxe Error\n");
		free(line);
		return (0);
	}
	return (1);
}
