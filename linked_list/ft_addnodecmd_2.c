/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addnodecmd_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:20:56 by abait-ou          #+#    #+#             */
/*   Updated: 2024/10/26 10:31:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"


int ft_argscalculation(t_token *tokens)
{
    int length;

    length = 0;
    while (tokens)
    {
        if (tokens->type == PIPE)
            break;
        length++;
        tokens = tokens->next;
    }
    return (length);
}

t_cmd *ft_returnlastnodecmd2(t_cmd *list)
{
    if (!list)
        return NULL;
    while (list->next)
    {
        list = list->next;   
    }
    return (list);
}

t_token *ft_nodecmdinit(t_cmd **node, t_token *token)
{
    int length;
    
    (*node)->args = (char **)malloc(sizeof(char *) * (ft_argscalculation(token) + 2));
    length = 0;
    while (token)
    {
        if (token->type == PIPE)
        {
            token = token->next;
            break ;
        }
        else if (!token->prev || (token->prev->type == PIPE && token))
        {
            (*node)->order = ft_strdup(token->cmd);
            token = token->next;
            continue ;
        }
        else if (token->prev || token->prev->type != PIPE)
        {
            (*node)->args[length++] = ft_strdup(token->cmd);
            token = token->next;
            continue ;
        }
    }
    (*node)->args[length] = NULL;
    return (token);
}






t_token *ft_addnodecmd(t_shell *shell, t_token *token)
{
    t_cmd *node;
    t_cmd *last_node;
    

    node = malloc(sizeof(t_cmd));
    if (!node)
        return (NULL);
    node->next = NULL;
    token = ft_nodecmdinit(&node, token);
    ft_redirectioninit(&node, shell);
    if (!(shell->cmd))
    {
        (shell->cmd) = node;
        node->prev = NULL;
    }
    else
    {
        last_node = ft_returnlastnodecmd2((shell->cmd));
        last_node->next = node;
        node->prev  = last_node;
    } 
    return (token);
}

static int ft_nodescalculation(t_token *token)
{
    int length;
    t_token *tokens;

    length = 0;
    tokens = token;
    
    while (tokens)
    {
        if (tokens->type == PIPE)
        {
            length++;
            if (token->next->type == PIPE)
                token = token->next;
        }
        tokens = tokens->next;
    }
    
    return (length);
}

void ft_cmdliste_2(t_shell *shell, t_token *token)
{
    int counter;
    int length;

    length = ft_nodescalculation(shell->tokens);
    while (length-- >= 0) 
            token = ft_addnodecmd(shell, token);
}










 // while (shell->cmd)
    // {
    //     printf("arg cmd [ ] %s\n", shell->cmd->order);
    //     while (shell->cmd->args[i])
    //     {
    //             printf("args [%d] %s\n", i, shell->cmd->args[i]);
    //             i++;
    //     }
    //     i = 0;
    //     shell->cmd = shell->cmd->next;
    // }

