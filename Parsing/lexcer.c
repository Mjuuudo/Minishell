/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:35:03 by abait-ou          #+#    #+#             */
/*   Updated: 2024/10/24 14:10:55 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"


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


void ft_parser(t_shell *shell)
{
   ft_cmdliste(shell);
   ft_cmdliste_2(shell, shell->tokens);  
   ft_freetokenmain(shell);
}


static void ft_lexcer(char *line, t_shell *shell)
{
    int length;

    length = count_spaces(line);
    shell->commande.commande = spaced_string(line, shell, length, 0);
    free(line);
    shell->commande.table = ft_split(shell->commande.commande, " \n\t\v\f\r");
    free(shell->commande.commande);
}


void  ft_cmdhandler(char *line, t_shell *shell)
{
    if (ft_quotesch(line, shell) && ft_pipe(line, shell))
    {
        ft_lexcer(line, shell);
        ft_parser(shell);
        ft_freefirstcmd(shell);
    }
}