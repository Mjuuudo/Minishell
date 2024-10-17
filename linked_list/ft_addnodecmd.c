/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addnodecmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:44:17 by abait-ou          #+#    #+#             */
/*   Updated: 2024/10/17 13:08:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"


void   ft_initnodecmd(t_token *node, char *value)
{
   node->cmd =ft_strdup(value);
   if (!ft_strncmp(value, "<", ft_strlen(value)))
		node->type = LESS;
	else if (!ft_strncmp(value, ">", ft_strlen(value)))
		node->type = GREAT;
	else if (!ft_strncmp(value, "<<", ft_strlen(value)))
		node->type = LLESS;
	else if (!ft_strncmp(value, ">>", ft_strlen(value)))
		node->type = DGREAT;
	else if (!ft_strncmp(value, "|", ft_strlen(value)))
		node->type = PIPE;
	else
		node->type = STR;
}

t_token *ft_returnlastnodecmd(t_token *list)
{
   if (!list)
        return NULL;
    
    while (list->next)
    {
        list = list->next;  
    }
    return (list);
}

void ft_cmdliste(t_shell *shell)
{
    t_token *node;
    t_token *last_node;
    int counter;

    counter = 0;
    while (shell->commande.table[counter] != NULL)
    {
        node = malloc(sizeof(t_token));
        if (!node)
            return ;
        node->next = NULL;
        ft_initnodecmd(node, shell->commande.table[counter]);
         printf("here\n");
        ft_expand(node, shell->envp);
        if (!shell->tokens)
        {
            shell->tokens = node;
            node->prev = NULL;
        }
        else
        {
            last_node = ft_returnlastnodecmd(shell->tokens);
            last_node->next = node;
            node->prev  = last_node;
        }   
        counter++;
    }
}

