/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addnodecmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:44:17 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/11 14:33:42 by abait-ou         ###   ########.fr       */
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

void ft_morethan2(t_token *node, t_shell *shell)
{
    char **holder;
    int counter;
    t_token *last_node;

    holder = ft_split(node->cmd, " \n\t\v\f\r");
    free(node->cmd);
    free(node);
    counter = 0;
    while (holder[counter] != NULL)
    {
        node = malloc(sizeof(t_token));
        if (!node)
                return ;
        node->next = NULL;
        ft_initnodecmd(node, holder[counter]);
        
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
    counter = 0;
    while (holder[counter])
        free(holder[counter++]);
    free(holder);
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
        if (ft_expand(node, shell->envp) <= 1)
        { 
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
        else
        {
                ft_morethan2(node, shell);
                counter++;
        }
    }
}

