/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addnodefile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:47:27 by marvin            #+#    #+#             */
/*   Updated: 2024/10/22 13:47:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

static t_types get_ident(char *option)
{
    if (!ft_strcmp(option, ">>"))
        return (DGREAT);
    else if (!ft_strcmp(option, ">"))
        return (GREAT);
    else if (!ft_strcmp(option, "<<"))
        return (LLESS);
    else if (!ft_strcmp(option, "<"))
        return (LESS);
    return (NONE);
}


static t_redirection *ft_returnlastnodered(t_redirection *list)
{
   if (!list)
        return NULL;
    
    while (list->next)
    {
        list = list->next;  
    }
    return (list);
}

void *ft_addnodefile(char *option, char *file, t_redirection **liste)
{
    t_redirection *node;
    t_redirection *last_node;
    

    node = malloc(sizeof(t_redirection));
    if (!node)
        return (NULL);
    node->next = NULL;
    node->file = ft_strdup(file);
    node->identifier = get_ident(option);
    if (!(*liste))
    {
        (*liste) = node;
        node->prev = NULL;
    }
    else
    {
        last_node = ft_returnlastnodered((*liste));
        last_node->next = node;
        node->prev  = last_node;
    } 
    return NULL;
}


void ft_redirectioninit(t_cmd **node, t_shell *shell)
{
    t_cmd *array;
    int counter;

    counter = 0;
    array = (*node);
    (void)shell;  // Unused parameter
    (*node)->red = NULL;

    // Potential problem starts here
    if (ft_checkred((*node)->red2, (*node)->order))
    {
       
        if (ft_isredornot((*node)->order))
            // First potential problematic line
            ft_addnodefile(((*node)->order), (*node)->red2[counter++], &(*node)->red);

        while (array->red2[counter])  // Potential out-of-bounds access
        {
            if (ft_isredornot(array->red2[counter]))
            {
                // Second potential problematic line
                ft_addnodefile(array->red2[counter], array->red2[counter + 1], &(*node)->red);
                counter++;
            }
            counter++;
        }
    }
    else
    {
        (*node)->red = NULL;
        return ;
    }
}