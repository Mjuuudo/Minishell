/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:50:34 by abait-ou          #+#    #+#             */
/*   Updated: 2024/10/02 14:19:25 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

int ft_quotes(char *line, int index)
{
    int counter;
    char sym;
    int start;
    int end;
    
    counter = 0;
    while (line[counter])
    {
        if (line[counter] == 39 || line[counter] == '"')
        {
            start = counter;
            sym = line[counter++];
            while(line[counter] != sym && line[counter])
                counter++;
            end = counter;
             if (start <= index && end >= index)
                return (1);
        }
        counter++;
    }
    return (0);
}


// void ft_spacedstring(char *line, int spaces, char *dest, int counter_2)
// {
//     int counter_1;
    
//     counter_1 = 0;
//     while (line[counter_1])
//     {
//         if ((line[counter_1] == '|' || line[counter_1] == '>' || line[counter_1] == '<') 
//                     && !ft_quotes(line, counter_1))
//         {
//             dest[counter_2++] = ' ';
//             if (line[counter_1] == '>' || line[counter_1] == '<')
//             {
//                 dest[counter_2++] = line[counter_1];
//                 if (line[counter_1] == line[counter_1 + 1])
//                     dest[counter_2++] = line[counter_1++];
//             }
//             else
//                 dest[counter_2++] = '|';
//             dest[counter_2++] = ' ';
//             counter_1++;
//         }
//         else
//             dest[counter_2++] = line[counter_1++];
//     }
//    dest[counter_2] = '\0';
// } Tooo remove

// void ft_formatcorrection(t_shell *shell, char *line)
// {
//     int spaces;
//     char *spaced_string;
//     int counter_2;
//     int i = 0;

//     spaces = 0;
//     counter_2 = 0;
//     spaces += ft_spacecalculation(line);
//     spaced_string = malloc(sizeof(char) * (spaces + ft_strlen(line) + 1));
//     if (!spaced_string)
//         return ;
//     ft_spacedstring(line, spaces, spaced_string, counter_2);
//     shell->commande.commande  = spaced_string;
//     printf("%s\n", (*shell).commande.commande); // Printf F To Remove
// }    Tooo Remove

// void    ft_lexcer(char *commande, t_shell *shell)
// {
//     int length;
//     int i = 0;
    
//     length = ft_spacecalculation(commande);
//     ft_formatcorrection(shell, commande);
//     shell->commande.table = ft_split((*shell).commande.commande, ' ');
//     while ((shell)->commande.table[i])
//     {
//         printf("arg [%d] %s\n", i, (shell)->commande.table[i]);
//         i++;
//     }   //Loop Used To Print The Elements Of The Commande Table
//     // ft_freecmd(shell->commande.commande, shell->commande.table);
// }

// Todo Improvements About the ft_split To Support All Spacing Chars

void ft_shell_on(t_shell *shell)
{
    char *line;
    int rl_status;

    
    while (shell->exit == 0)
    {
        line = readline("Blackhole_Lover's@Minis(hell):~$");
        if (line)
            ft_cmdhandler(line, shell);
        else if (!line)
            shell->exit = 1;
        else
            printf("\n");
    }
    // free(line);
}