/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addnodecmd_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:20:56 by abait-ou          #+#    #+#             */
/*   Updated: 2024/10/03 21:08:25 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"


int ft_argscalculation(t_token *tokens)
{
    int length;
    while (tokens)
    {
        if (tokens->type == PIPE)
            break;
        length++;
        tokens = tokens->next;
    }
    return (length);
}
// Tokens true
static t_token *ft_initcmdnode(t_shell *shell, t_cmd **cmd, t_token *tokens)
{   
    t_token *tmp;
    int length;

    tmp = tokens;
    length = ft_argscalculation(tmp);
    while ((*cmd))
    {
        while (tmp)
        {
            if  (tmp->prev->type == PIPE || !tmp->prev)
            {
                (*cmd)->order = ft_strdup(tmp->cmd);
                tmp = tmp->next;
            }
            else if (tmp->type == PIPE)
            {
                tmp = tmp->next;
                break ;
            }
            else
                tmp = tmp->next;
        }
        (*cmd) = (*cmd)->next;
    }
    // while (tokens)
    // {
    //     printf("%s\n", tokens->cmd);
    //     tokens = tokens->next;
    // }
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



void ft_addnodecmd(t_shell *shell)
{
    t_cmd *node;
    t_cmd *last_node;

    node = malloc(sizeof(t_cmd));
    if (!node)
        return ;
    node->next = NULL;
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
}
// check tokens true
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

// check tokens true
void ft_cmdliste_2(t_shell *shell, t_token *token)
{

    
    int counter;
    int length;

    length = ft_nodescalculation(shell->tokens);
    if (length == 0)
        length++;
    while (length-- > 0) 
        ft_addnodecmd(shell);
    ft_initcmdnode(shell, shell->cmd, shell->tokens);
    // int i = 0;
    // while (shell->tokens)
    // {
    //     printf("arg[%d]: %s  %d\n", i, shell->tokens->cmd, shell->tokens->type);
    //     i++;
    //     shell->tokens = shell->tokens->next;
    // }
    // counter = 0;
    // ft_addnodecmd(shell);
    // shell->tokens = ft_initcmdnode(shell, shell->cmd,shell->tokens);
    // ft_addnodecmd(shell);
    // shell->tokens = ft_initcmdnode(shell, shell->cmd,shell->actual);
    // // ft_addnodecmd(shell);
    // // shell->tokens = ft_initcmdnode(shell, shell->cmd,shell->actual);
    while (shell->cmd)
    {
        printf("%s\n", shell->cmd->order);
        shell->cmd = shell->cmd->next;
    }
}

