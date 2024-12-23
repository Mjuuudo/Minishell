/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 10:01:12 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/23 01:34:53 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

bool	find_env_var_appending(t_envvar *env_list, char *str)
{
	char	*plus_pos;
	char	*new_str;
	size_t	key_length;

	plus_pos = ft_strchr2(str, '+');
	if (!plus_pos)
		return (false);
	key_length = (size_t)(plus_pos - str);
	new_str = strndup(str, key_length);
	if (!new_str)
		return (false);
	while (env_list)
	{
		if (strcmp(env_list->key, new_str) == 0)
		{
			return (true);
		}
		env_list = env_list->next;
	}
	return (false);
}

int	update_the_env_var_appending(t_envvar *env_list, char *str)
{
	char	*equal_pos;
	char	*plus_pos;
	size_t	key_lenght;
	char	*new_str;
	char	*old_value;

	key_lenght = 0;
	equal_pos = ft_strchr2(str, '=');
	plus_pos = ft_strchr2(str, '+');
	if (!equal_pos || !plus_pos)
		return (1);
	key_lenght = (size_t)(plus_pos - str);
	new_str = strndup(str, key_lenght);
	while (env_list)
	{
		if (strcmp(env_list->key, new_str) == 0)
		{
			old_value = env_list->value;
			env_list->value = join2(old_value, equal_pos + 1);
			return (0);
		}
		env_list = env_list->next;
	}
	return (1);
}

int	add_to_env_var_appending(t_envvar *env_list, char *str)
{
	char	*equal_pos;
	char	*plus_pos;
	size_t	key_lenght;

	equal_pos = ft_strchr2(str, '=');
	plus_pos = ft_strchr2(str, '+');
	key_lenght = (size_t)(plus_pos - str);
	while (env_list && env_list->next)
		env_list = env_list->next;
	env_list->next = ft_malloc(sizeof(t_envvar), 'm');
	env_list->next->next = NULL;
	env_list->next->prev = env_list;
	{
		env_list->next->key = ft_strndup(str, key_lenght);
		env_list->next->value = ft_strdup(equal_pos + 1);
	}
	return (0);
}

int	appending_env_var(t_envvar *env_list, char *str)
{
	if (find_env_var_appending(env_list, str))
	{
		if (update_the_env_var_appending(env_list, str) == 0)
			return (0);
		else
			return (1);
	}
	else
	{
		printf("adding\n");
		add_to_env_var_appending(env_list, str);
	}
	return (0);
}

char	*ft_str_join(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len1;
	size_t	len2;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	len1 = 0;
	len2 = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = (char *)ft_malloc(sizeof(char) * (len1 + len2 + 1), 'm');
	if (ptr == NULL)
		return (NULL);
	i = 0;
	i += ft_str_lcpy(ptr + i, s1, len1 + 1);
	i += ft_str_lcpy(ptr + i, s2, len2 + 1);
	ptr[len1 + len2] = '\0';
	return (ptr);
}
