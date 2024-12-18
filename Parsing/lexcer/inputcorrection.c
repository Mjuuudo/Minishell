/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputcorrection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:27:13 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/18 11:27:43 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

static int	is_operator(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

static char	*prepare_spaced_string(size_t max_possible_len)
{
	char	*spaced_string;

	spaced_string = malloc(max_possible_len);
	if (!spaced_string)
		return (NULL);
	return (spaced_string);
}

static int	handle_operator_spacing(char *line, char *spaced_string,
		size_t *write_index, size_t *counter)

{
	if (*write_index >= shell.max_possible_len - 2)
		return (0);
	spaced_string[(*write_index)++] = ' ';
	if (is_operator(line[*counter + 1]))
		spaced_string[(*write_index)++] = line[(*counter)++];
	spaced_string[(*write_index)++] = line[*counter];
	spaced_string[(*write_index)++] = ' ';
	return (1);
}

static char	*add_spaces_around_operators(char *line, size_t write_index,
		size_t counter)
{
	size_t	line_len;
	char	*spaced_string;

	line_len = ft_strlen(line);
	shell.max_possible_len = line_len + (line_len * 2) + 1;
	spaced_string = prepare_spaced_string(shell.max_possible_len);
	if (!spaced_string)
		return (NULL);
	while (line[counter])
	{
		if (is_operator(line[counter]) && !ft_quotes(line, counter))
		{
			if (!handle_operator_spacing(line, spaced_string, &write_index,
					&counter))
				return (free(spaced_string), NULL);
		}
		else
			spaced_string[write_index++] = line[counter];
		counter++;
	}
	spaced_string[write_index] = '\0';
	return (spaced_string);
}

char	*spaced_string(char *line, t_shell *shell, int spaces, int counter_2)
{
	return (add_spaces_around_operators(line, 0, 0));
}
