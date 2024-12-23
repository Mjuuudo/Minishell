/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:25:08 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/22 23:28:36 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

t_envvar	*free_node(t_envvar **head, t_envvar *node)
{
	t_envvar	*tmp;

	if (node == NULL)
		return (NULL);
	if (node == *head)
		*head = node->next;
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	tmp = node->next;
	if (node->value)
		return (tmp);
	return (tmp);
}

void	find_and_free_env_var(t_envvar **env_list, char *str)
{
	t_envvar	*current;

	if (!env_list || !*env_list || !str)
		return ;
	current = *env_list;
	while (current)
	{
		if (strcmp(current->key, str) == 0)
		{
			free_node(env_list, current);
			return ;
		}
		current = current->next;
	}
}

int	unset_builtin(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->order || !cmd->args || !cmd->args[0])
		return (1);
	while (cmd->args[i] != NULL)
	{
		if (strcmp(cmd->args[i], "_") == 0)
			continue ;
		else
			find_and_free_env_var(&shell.envp, cmd->args[i]);
		i++;
	}
	shell.exit = 0;
	return (0);
}

bool	ft_isalpha2(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (true);
	return (false);
}
