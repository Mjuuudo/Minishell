/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:35:03 by abait-ou          #+#    #+#             */
/*   Updated: 2024/10/03 18:58:04 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

// TODO Create The fucntion That Translate The Previous linked Liste Into A new One Usable

static int ft_nodescalculation(t_shell *shell)
{
    int length;

    length = 1;
    while (shell->tokens)
    {
        if (shell->tokens->type == 0)
        {
            length++;
            if (shell->tokens->next->type == 0)
                shell->tokens = shell->tokens->next;
        }
        shell->tokens = shell->tokens->next;
    }
    return (length);
}

void ft_ordersfill(t_shell **shell)
{
    printf("arg : \n");
    while ((*shell)->tokens)
    {
        printf("[] %s\n", (*shell)->tokens->cmd);
        (*shell)->tokens = (*shell)->tokens->next;
    }
    // while (shell->tokens)
    // {
        
    //     if (shell->tokens->prev == NULL || shell->tokens->prev->type == PIPE)
    //     {
            
    //         shell->cmd->order = ft_strdup(shell->tokens->cmd);
    //         shell->cmd = shell->cmd->next;
    //     }
    //     shell->tokens = shell->tokens->next;
    // }
}

void ft_parser(t_shell *shell)
{
   ft_cmdliste_2(shell, shell->tokens);  
    
}


static void ft_lexcer(char *line, t_shell *shell)
{
    int length;

    length = count_spaces(line);
    shell->commande.commande = spaced_string(line, shell, length, 0);
    free(line);
    shell->commande.table = ft_split(shell->commande.commande, " \n\t\v\f\r");
    free(shell->commande.commande);
    ft_cmdliste(shell);
    
}


void  ft_cmdhandler(char *line, t_shell *shell)
{
    ft_redirections(line, shell);
    ft_pipe(line, shell);
    ft_quotesch(line, shell);
    ft_lexcer(line, shell);
    // int i = 0;
    // while (shell->tokens && shell->tokens != NULL)
    // {
    //     printf("arg[%d]: %s  %d\n", i, shell->tokens->cmd, shell->tokens->type);
    //     i++;
    //     shell->tokens = shell->tokens->next;
    // }
    // printf("arg : \n");
    // while (shell->tokens)
    // {
    //     printf("[] %s\n", shell->tokens->cmd);
    //     shell->tokens = shell->tokens->next;
    // }
    ft_parser(shell);
    
}