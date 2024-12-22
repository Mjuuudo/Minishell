/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addnodeenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 20:27:57 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/22 11:43:29 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

void	ft_initnodeenv(t_envvar *node, char *value)
{
	int	start;
	int	counter;

	counter = 0;
	start = 0;
	while (value[counter] && value[counter] != '=' && value[counter] != '\n')
		counter++;
	node->key = ft_malloc(sizeof(char) * (counter + 1), 'm');
	if (!node->key)
		return ;
	ft_strncpy(node->key, value, counter);
	node->key[counter++] = '\0';
	start = counter;
	while (value[counter] && value[counter != '\n'])
		counter++;
	node->value = ft_malloc(sizeof(char) * (counter - start + 1), 'm');
	if (!node->value)
		return ;
	ft_strncpy(node->value, value + start, counter - start);
	node->value[counter - start] = '\0';
}

t_envvar	*ft_returnlastnodeenv(t_envvar *list)
{
	if (!list)
		return (NULL);
	while (list->next)
	{
		list = list->next;
	}
	return (list);
}

void	ft_addnodeenv(t_envvar **list, char *value)
{
	t_envvar	*node;
	t_envvar	*last_node;

	if (value)
		node = ft_malloc(sizeof(t_envvar), 'm');
	if (!node)
		return ;
	node->next = NULL;
	ft_initnodeenv(node, value);
	if (!(*list))
	{
		(*list) = node;
		node->prev = NULL;
	}
	else
	{
		last_node = ft_returnlastnodeenv((*list));
		last_node->next = node;
		node->prev = last_node;
	}
}
