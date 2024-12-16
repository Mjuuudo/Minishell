/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:45:28 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/13 11:42:30 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"


//TODO CLEAN UP WHIT
/**
 * !I need to handle leaks
 * !also the node (env_list->next->next) should be created (ask about it)
 * !The case where it goes export a b c d should make them all.
 * !make the exit value
 * !make the error message
 * !split the files.
 */


// bool	ft_isalnum(char c)
// {
// 	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
// 			&& c <= '9') || c == '_')
// 		return (true);
// 	return (false);
// }

bool	ft_isalpha2(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (true);
	return (false);
}

// size_t	my_strlen(const char *str, const char *end)
// {
// 	const char	*ptr = str;

// 	if (end == NULL || end < str)
// 	{
// 		return (0);
// 	}
// 	while (ptr < end && *ptr != '\0')
// 	{
// 		ptr++;
// 	}
// 	return ((size_t)(ptr - str));
// }

bool	find_env_var(t_envvar *env_list, char *str)
{
	char	*equal_pos;
	size_t	key_lenght;

	equal_pos = strchr(str, '=');
	if (equal_pos == NULL)
		key_lenght = strlen(str);
	else
		key_lenght = (size_t)(equal_pos - str);
	while (env_list)
	{
		if (strncmp(env_list->key, str, key_lenght) == 0)
			return (true);
		env_list = env_list->next;
	}
	return (false);
}

// TODO CHECK THE CASE OF VAR===ALL

int	is_valid_identifier(char *str)
{
	char	*equals_pos;

	if (!str || *str == '\0')
		return (false);
	equals_pos = strchr(str, '=');
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
	// size_t	value_lenght;

	equal_pos = strchr(str, '=');
	if (equal_pos == NULL)
		return (1);
	else
		key_lenght = (size_t)(equal_pos - str);
	// value_lenght = strlen(str) - key_lenght - 1;
	while (env_list)
	{
		if (strncmp(env_list->key, str, key_lenght) == 0)
		{
			env_list->value = strdup(equal_pos + 1);
			return (0);
		}
		env_list = env_list->next;
	}
	return (1);
}

int	update_the_env_var2(t_envvar *env_list, char *value)
{
	char	*equal_pos;
	size_t	key_lenght;
	char 	*key;
	char    *new_value;

	equal_pos = strchr(value, '=');
	if (!equal_pos)
		return (1);

	key_lenght = (size_t)(equal_pos - value);
	key = strndup(value, key_lenght);
	if (!key)
		return (1);
	new_value = strdup(equal_pos + 1);
	if (!new_value)
	{
		free(key);
		return (1);
	}
	while (env_list)
	{
		if (strcmp(env_list->key, key) == 0)
		{
			free(env_list->value);
			env_list->value = new_value;
			free(key);
			return (0);
		}
		env_list = env_list->next;
	}
	free(key);
	free(new_value);
	return (1);
}

int	add_to_env_var(t_envvar *env_list, char *str)
{
	char	*equal_pos;
	size_t	key_lenght;

	equal_pos = strchr(str, '=');
	if (equal_pos == NULL)
		key_lenght = strlen(str);
	else
		key_lenght = (size_t)(equal_pos - str);
	while (env_list && env_list->next)
		env_list = env_list->next;
	env_list->next = malloc(sizeof(t_envvar));
	// TODO HANDLE LEAKS
	env_list->next->next = NULL;
	env_list->next->prev = env_list;
	if (equal_pos == NULL)
	{
		env_list->next->key = strdup(str);
		env_list->next->value = NULL;
	}
	else
	{
		env_list->next->key = strndup(str, key_lenght);
		env_list->next->value = strdup(equal_pos + 1);
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
	int			i;

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
		{
			printf("Error: Unknown option %s\n",cmd->args[i]);
			// error_occured = true; // idont remeber why i  did this
			// exit(1);
		}
		// TODO IF EEROR OCCURED THE EXIT STATUS SHOULD BE 1s
		i++;
	}
	// print_envvar(cmd->args[i]);
	return (0);
}

//TODO THE CASE : VAR+=2 3 4
//3 AND 4 SHOULD BE UNVALID NOT VALID