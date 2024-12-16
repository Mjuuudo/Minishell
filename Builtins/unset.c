/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:25:08 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/14 15:09:18 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"


t_envvar *free_node(t_envvar **head, t_envvar *node)
{
    t_envvar *tmp;

    if (node == NULL)
        return (NULL);

    // Update head if removing the first node
    if (node == *head)
        *head = node->next;

    // Update prev and next links
    if (node->prev)
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;

    // Store next node before freeing
    tmp = node->next;

    // Free node contents
    free(node->key);
    if (node->value)
        free(node->value);
    free(node);

    return (tmp);
}

void find_and_free_env_var(t_envvar **env_list, char *str)
{
    t_envvar *current;

    if (!env_list || !*env_list || !str)
        return;

    current = *env_list;
    while (current)
    {
        if (strcmp(current->key, str) == 0)
        {
            free_node(env_list, current);
            return;
        }
        current = current->next;
    }
}

void update_shlvl(t_envvar *env_list)
{
	while (env_list)
	{
		if (strcmp(env_list->key, "SHLVL") == 0)
		{
			int current_level = env_list->value ? atoi(env_list->value) : 0;
			free(env_list->value);
			if (current_level <= 1)
				env_list->value = strdup("0");
			else
			{
				char new_level[16];
				snprintf(new_level, sizeof(new_level), "%d", current_level - 1);
				env_list->value = strdup(new_level);
			}
			return;
		}
		env_list = env_list->next;
	}
}


int unset_builtin(t_cmd *cmd)
{
	int i;

	// Check if there are any arguments to unset
	if (!cmd->order || !cmd->args || !cmd->args[0])
		return (1);

	for (i = 0; cmd->args[i] != NULL; i++)
	{
		// Handle special case for SHLVL
		// if (strcmp(cmd->args[i], "SHLVL") == 0)
		// 	update_shlvl(shell.envp);
		if (strcmp(cmd->args[i], "_") == 0)
			continue;
		else
			find_and_free_env_var(&shell.envp, cmd->args[i]);
	}
	return (0);
}



// void	find_and_free_env_var(t_envvar *env_list, char *str)
// {
// 	char	*equal_pos;
// 	size_t	key_lenght;
// 	size_t	value_lenght;

// 	equal_pos = strchr(str, '=');
// 	if (equal_pos == NULL)
// 		key_lenght = strlen(str);
// 	else
// 	{
// 		key_lenght = (size_t)(equal_pos - str);
// 		value_lenght = strlen(str) - key_lenght - 1;
// 	}
// 	while (env_list)
// 	{
// 		if ((equal_pos == NULL && strncmp(env_list->key, str, key_lenght) == 0 && env_list->value == NULL) ||
// 			(equal_pos != NULL && strncmp(env_list->key, str, key_lenght) == 0 &&
// 			strcmp(env_list->value, equal_pos + 1) == 0))
// 		{
// 			env_list = free_node(env_list);
// 			return;
// 		}
// 		env_list = env_list->next;
// 	}
// }
