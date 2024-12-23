/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:45:28 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/23 01:35:32 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

bool	find_env_var(t_envvar *env_list, char *str)
{
	char	*equal_pos;
	size_t	key_lenght;

	equal_pos = ft_strchr2(str, '=');
	if (equal_pos == NULL)
		key_lenght = ft_strlen(str);
	else
		key_lenght = (size_t)(equal_pos - str);
	while (env_list)
	{
		if (ft_strncmp(env_list->key, str, key_lenght) == 0)
			return (true);
		env_list = env_list->next;
	}
	return (false);
}

int	is_valid_identifier(char *str)
{
	char	*equals_pos;

	if (!str || *str == '\0')
		return (false);
	equals_pos = ft_strchr2(str, '=');
	if (!ft_isalpha2(*str) && *str != '_')
		return (3);
	str++;
	while (*str && (equals_pos == NULL || str < equals_pos))
	{
		if (!ft_isalnum(*str) && *str != '_')
		{
			if (*str == '+' && *(str + 1) == '=')
				return (2);
			else
				return (1);
		}
		str++;
	}
	return (0);
}

int	update_the_env_var(t_envvar *env_list, char *str)
{
	char	*equal_pos;
	size_t	key_lenght;

	equal_pos = ft_strchr2(str, '=');
	if (equal_pos == NULL)
		return (1);
	else
		key_lenght = (size_t)(equal_pos - str);
	while (env_list)
	{
		if (ft_strncmp(env_list->key, str, key_lenght) == 0)
		{
			env_list->value = ft_strdup(equal_pos + 1);
			return (0);
		}
		env_list = env_list->next;
	}
	return (1);
}

int	update_existing_env_var(t_envvar *env_list, char *key, char *new_value)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
		{
			env_list->value = new_value;
			return (0);
		}
		env_list = env_list->next;
	}
	return (1);
}

int	parse_key_value(char *value, char **key, char **new_value)
{
	char	*equal_pos;
	size_t	key_length;

	equal_pos = strchr(value, '=');
	if (!equal_pos)
		return (1);
	key_length = (size_t)(equal_pos - value);
	*key = ft_strndup(value, key_length);
	if (!*key)
		return (1);
	*new_value = ft_strdup(equal_pos + 1);
	if (!*new_value)
		return (1);
	return (0);
}
