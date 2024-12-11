/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:35:03 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/11 13:17:37 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"




void ft_parser(t_shell *shell)
{
//    t_token *tk;

   ft_cmdliste(shell);
//    tk = shell->tokens;
//     int  i = 0;
    // while (tk)
    // {
    //     printf("arg tokens[%d]: %s  %d\n", i, tk->cmd, tk->type);
    //     i++;
    //     tk = tk->next;
    // }
   ft_cmdliste_2(shell, shell->tokens);  
   ft_freetokenmain(shell);
}


static void ft_lexcer(char *line, t_shell *shell)
{
    int length;

    length = count_spaces(line);
    shell->commande.commande = spaced_string(line, shell, length, 0);
    // int i = 0;
    // while (shell->commande.commande[i])
    //     printf("%s\n", shell->commande.commande[i++]);
    free(line);
    shell->commande.table = ft_split(shell->commande.commande, " \n\t\v\f\r");
    free(shell->commande.commande);
}


void  ft_cmdhandler(char *line, t_shell *shell)
{
    
    if (ft_quotesch(line, shell) && ft_pipe(line, shell)
        && ft_redirections(line, shell))
    {
        ft_lexcer(line, shell);
        ft_parser(shell);
        ft_freefirstcmd(shell);
    }
}