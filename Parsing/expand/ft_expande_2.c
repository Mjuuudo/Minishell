/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expande_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:29:36 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/18 15:09:58 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

int	isinornot(const char *arg, int in_quote, int i, int double_quote_count)
{
	int	single_quote_count;

	single_quote_count = 0;
	while (arg[i])
	{
		if (arg[i] == '"' && in_quote != 1)
		{
			in_quote = norm_2(in_quote);
			double_quote_count++;
		}
		else if (arg[i] == '\'' && in_quote != 2)
		{
			in_quote = norm_3(in_quote);
			single_quote_count++;
		}
		i++;
	}
	if (single_quote_count > double_quote_count)
		return (1);
	else if (double_quote_count > single_quote_count)
		return (2);
	else
		return (0);
}

int	ft_checkdollar(char *arg)
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

char	*retrivevalue(t_envvar *env, char *key)
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

int	foundornot(char *line, t_envvar *env)
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

int	is_valid_var_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}
