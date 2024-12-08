/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sorting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:26:57 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/02 09:11:51 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

// void	print_envvar(t_envvar *env_list)
// {
// 	while (env_list && env_list->next)
// 	{
// 		printf("%s=%s\n", env_list->key, env_list->value);
// 		env_list = env_list->next;
// 	}
// }

// bool	is_sorted(t_envvar *env_list)
// {
// 	while (env_list && env_list->next)
// 	{
// 		if (strcmp(env_list->key, env_list->next->key) > 0)
// 		{
// 			return (false);
// 		}
// 		else if (strcmp(env_list->key, env_list->next->key) == 0)
// 		{
// 			if (strcmp(env_list->value, env_list->next->value) > 0)
// 				return (false);
// 		}
// 		env_list = env_list->next;
// 	}
// 	return (true);
// }

// void	swap_nodes(t_envvar *a, t_envvar *b)
// {
// 	char	*temp;

// 	temp = a->key;
// 	a->key = b->key;
// 	b->key = temp;
// 	temp = a->value;
// 	a->value = b->value;
// 	b->value = temp;
// }

// void	bubble_sort(t_envvar *env_list)
// {
// 	t_envvar	*temp;

// 	temp = env_list;
// 	while (env_list && env_list->next)
// 	{
// 		if (!is_sorted(env_list))
// 		{
// 			env_list = temp;
// 			while (env_list && env_list->next)
// 			{
// 				if (strcmp(env_list->key, env_list->next->key) > 0)
// 					swap_nodes(env_list, env_list->next);
// 				else if (strcmp(env_list->key, env_list->next->key) == 0)
// 				{
// 					if (strcmp(env_list->value, env_list->next->value) > 0)
// 						swap_nodes(env_list, env_list->next);
// 				}
// 				env_list = env_list->next;
// 			}
// 		}
// 		else
// 			return ;
// 		env_list = temp;
// 		env_list = env_list->next;
// 	}
// }

// void	sort_the_linkedlist(t_envvar *env_list)
// {
// 	if (env_list == NULL || env_list->next == NULL)
// 		return ;
// 	if (!is_sorted(env_list))
// 		bubble_sort(env_list);
// 	print_envvar(env_list);
// }

void	print_envvar(t_envvar *env_list)
{
	while (env_list)
	{
		printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
}

bool	is_sorted(t_envvar *env_list)
{
	while (env_list && env_list->next)
	{
		if (strcmp(env_list->key, env_list->next->key) > 0)
		{
			return (false);
		}
		else if (strcmp(env_list->key, env_list->next->key) == 0)
		{
			if (strcmp(env_list->value, env_list->next->value) > 0)
				return (false);
		}
		env_list = env_list->next;
	}
	return (true);
}

void	swap_nodes(t_envvar *a, t_envvar *b)
{
	char	*temp;

	temp = a->key;
	a->key = b->key;
	b->key = temp;
	temp = a->value;
	a->value = b->value;
	b->value = temp;
}

void	bubble_sort(t_envvar *env_list)
{
	t_envvar	*temp;

	temp = env_list;
	while (env_list && env_list->next)
	{
		if (!is_sorted(env_list))
		{
			env_list = temp;
			while (env_list && env_list->next)
			{
				if (strcmp(env_list->key, env_list->next->key) > 0)
					swap_nodes(env_list, env_list->next);
				else if (strcmp(env_list->key, env_list->next->key) == 0)
				{
					if (strcmp(env_list->value, env_list->next->value) > 0)
						swap_nodes(env_list, env_list->next);
				}
				env_list = env_list->next;
			}
		}
		else
			return ;
		env_list = temp;
		env_list = env_list->next;
	}
}

void	sort_the_linkedlist(t_envvar *env_list)
{
	if (env_list == NULL || env_list->next == NULL)
		return ;
	if (!is_sorted(env_list))
		bubble_sort(env_list);
	print_envvar(env_list);
}

/**
 * ?Sorts the linked list of environment variables and prints the sorted list.
 *
 * @param env_list A pointer to the head of the linked list.
 * The function checks if the list is empty or has only one node,
 * sorts the list if necessary, and prints the result.
 */
/**
 *?Sorts the linked list of environment
 *?variables using the bubble sort algorithm.
 *
 * @param env_list	A pointer to the head of the linked list.
 *                 The function sorts the list in-place.
 */
/**
 * ?Swaps the keys and values of two nodes in the linked list.
 *
 * @param a A pointer to the first node.
 * @param b A pointer to the second node.
 */
/**
 * ?Prints the environment variables in the linked list.
 *
* @param env_list
A pointer to the head of the linked list of environment variables.
* The function prints each key-value pair in the format "key=value".
 */
/**
 * ?Checks if the linked list of environment variables is sorted.
 *
 * @param env_list A pointer to the head of the linked list.
 * @return true if the list is sorted by key (and value if keys are equal),
	false otherwise.
 */