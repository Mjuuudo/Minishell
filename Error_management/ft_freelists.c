/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freelists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 21:18:24 by abait-ou          #+#    #+#             */
/*   Updated: 2024/09/16 17:10:30 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

void ft_freeenv(t_envvar    *list)
{
    t_envvar *tmp;
    t_envvar *current;

    current = list;
    tmp = current->next;
    while (tmp)
    {
        tmp = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = tmp;
    }
}

void ft_freeenvholder(char **envholder)
{
    int counter;

    counter = 0;
    while (envholder[counter])
    {
        free(envholder[counter]);
        counter++;
    }
    free(envholder);
}