/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 23:31:25 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/23 01:38:33 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

int	update_the_env_var2(t_envvar *env_list, char *value)
{
	char	*key;
	char	*new_value;

	key = NULL;
	new_value = NULL;
	if (parse_key_value(value, &key, &new_value))
		return (1);
	if (!update_existing_env_var(env_list, key, new_value))
	{
		return (0);
	}
	return (1);
}

int	add_to_env_var(t_envvar *env_list, char *str)
{
	char	*equal_pos;
	size_t	key_lenght;

	equal_pos = ft_strchr2(str, '=');
	if (equal_pos == NULL)
		key_lenght = ft_strlen(str);
	else
		key_lenght = (size_t)(equal_pos - str);
	while (env_list && env_list->next)
		env_list = env_list->next;
	env_list->next = ft_malloc(sizeof(t_envvar), 'm');
	env_list->next->next = NULL;
	env_list->next->prev = env_list;
	if (equal_pos == NULL)
	{
		env_list->next->key = ft_strdup(str);
		env_list->next->value = ft_strdup("");
	}
	else
	{
		env_list->next->key = strndup(str, key_lenght);
		env_list->next->value = ft_strdup(equal_pos + 1);
	}
	return (0);
}

void	find_or_update(t_envvar *env_list, char **str, int i)
{
	find_or_add(env_list, str[i]);
	update_the_env_var2(env_list, str[i]);
}

void	find_or_add(t_envvar *env_list, char *str)
{
	if (find_env_var(env_list, str))
		update_the_env_var(env_list, str);
	else
		add_to_env_var(env_list, str);
}

int	export_builtin(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->args[0])
		sort_the_linkedlist(shell.envp);
	while (cmd->args[i])
	{
		if (is_valid_identifier(cmd->args[i]) == 2)
			appending_env_var(shell.envp, cmd->args[i]);
		else if (is_valid_identifier(cmd->args[i]) == 0)
			find_or_update(shell.envp, cmd->args, i);
		else
			printf("Error: Unknown option %s\n", cmd->args[i]);
		i++;
	}
	return (0);
}
