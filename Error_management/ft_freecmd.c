/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:27:36 by abait-ou          #+#    #+#             */
/*   Updated: 2024/10/18 11:46:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"




void ft_freecmdmain(t_shell *shell)
{
    t_cmd *current;
    int i = 0;

    current = shell->cmd;
    while (shell->cmd)
    {
        shell->cmd = shell->cmd->next;
        free(current->order);
        while (current->args[i])
            free(current->args[i++]);
        free(current->args);
        free(current);
        current = shell->cmd;
        i = 0;
    }
    // free(hell->cmd);
}

void ft_freetokenmain(t_shell *shell)
{
    t_token *current;

    current = shell->tokens;
    while (shell->tokens)
    {
        shell->tokens = shell->tokens->next;
        free(current->cmd);
        free(current);
        current = shell->tokens;
    }
    // free(shell->tokens);
}

void ft_freefirstcmd(t_shell *shell)
{
    int i = 0;

    while (shell->commande.table[i])
    {
        free(shell->commande.table[i]);
        i++;
    }
    free(shell->commande.table);
}