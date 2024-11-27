/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:50:34 by abait-ou          #+#    #+#             */
/*   Updated: 2024/11/27 12:12:15 by abait-ou         ###   ########.fr       */
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
static void display_cmd(t_shell *shell)
{
    int i = 0;
    while (shell->cmd)
    {
        printf("arg cmd [ ] %s\n", shell->cmd->order);
        while (shell->cmd->args[i])
        {
                printf("-->  args [%d] %s\n", i, shell->cmd->args[i]);
                i++;
        }
        i = 0;
        printf("---------- Redirections -------------\n");
        while (shell->cmd->red)
        {
            
            printf ("File %s, Type %d\n", shell->cmd->red->file, shell->cmd->red->identifier);
            shell->cmd->red = shell->cmd->red->next;
        }
        printf("------------ End Redirection -----------\n");
        shell->cmd = shell->cmd->next;
    }
}


void ft_shell_on(t_shell *shell)
{
    char *line;
    
    t_shell *s;
    while (shell->exit == 0)
    {
        line = readline("Blackhole_Lover's@Minis(hell):~$");
        if (line)
        {
                ft_cmdhandler(line, shell);
                s = shell;
                display_cmd(s);
                // printf("current %s\n", shell->cmd->order);
                ft_freecmdmain(shell);
        }
        else if (!line)
            shell->exit = 1;
        else
            printf("\n");
    }
    printf("Exiting Shell ...\n");
    free(line);
}