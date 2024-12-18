/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expande_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:30:39 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/18 15:53:55 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

int	is_alnum_or_underscore(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	extract_var_name(char *input, char *holder, int *index)
{
	int	a;

	a = 0;
	while (input[*index] && (ft_isalnum(input[*index]) || input[*index] == '_'))
	{
		holder[a++] = input[(*index)++];
	}
	holder[a] = '\0';
	return (a);
}

int	handle_env_var(char *new_string, char *holder, t_envvar *env, int *counter)
{
	char	*itsvalue;
	int		val_index;

	itsvalue = retrivevalue(env, holder);
	val_index = 0;
	if (!foundornot(holder, env))
	{
		if (is_alnum_or_underscore(holder))
			return (1);
		return (0);
	}
	while (itsvalue[val_index])
		new_string[(*counter)++] = itsvalue[val_index++];
	free(itsvalue);
	return (1);
}
