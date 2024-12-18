/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputcorrection_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:02:38 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/18 11:28:48 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

int	count_spaces(char *line)
{
	int	counter;
	int	spaces;

	counter = 0;
	spaces = 0;
	while (line[counter])
	{
		if (line[counter] == '|' || line[counter] == '<'
			|| line[counter] == '>')
			spaces++;
		if (line[counter] && ((line[counter] == '>' && line[counter + 1] == '>')
				|| (line[counter] == '<' && line[counter + 1] == '<')))
			spaces--;
		counter++;
	}
	return (spaces);
}
