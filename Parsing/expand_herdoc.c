/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:41:53 by marvin            #+#    #+#             */
/*   Updated: 2024/12/19 12:59:33 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

int	ft_checkdollarher(char *arg)
{
	int	counter;

	counter = 0;
	while (arg[counter])
	{
		if (arg[counter] == '$')
		{
			return (1);
		}
		counter++;
	}
	return (0);
}

char	*retrivevalueher(t_envvar *env, char *key)
{
	char	*value;

	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key)))
		{
			value = ft_strdup(env->value);
			break ;
		}
		env = env->next;
	}
	return (value);
}

int	foundornother(char *line, t_envvar *env)
{
	if (!line || !env)
		return (0);
	while (env)
	{
		if (!env->key)
			continue ;
		if (ft_strcmp(line, env->key) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	read_var_name(char *line, int *i, char *holder)
{
	int	a;

	a = 0;
	while (line[*i] && is_valid_var_char(line[*i]))
		holder[a++] = line[(*i)++];
	holder[a] = '\0';
	return (a);
}
