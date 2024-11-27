/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:26:55 by abait-ou          #+#    #+#             */
/*   Updated: 2024/11/27 09:34:52 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

static int pipenumber(char *line, int counter)
{
    if (line[counter + 1] == '|')
    {
        counter++;
        while (line[counter])
        { 
            if (ft_ispace(line[counter]))
                counter++;
            else if(line[counter + 1] == '|')
                return (0);
            else
                break;
        }
    }
    return (1);
}

static int checkbefore(char *line, int counter)
{
    while (counter-- > 0)
    {
        if (!ft_ispace(line[counter]) && line[counter] != '\0')
            return (1);
    }
    return (0);
}

static int checkafter(char *line, int counter)
{
    while (line[counter] == '|')
        counter++;
    while (line[counter])
    {
        if (!ft_ispace(line[counter]) && line[counter] != '\0')
            return (1);
        counter++;
    }
    return (0);
}

static int pipecheck(char *line)
{
    int counter;

    counter = 0;
    while (line[counter])
    {
        if (line[counter] == '|' && !ft_quotes(line, counter))
        {
            if (!pipenumber(line, counter))
                return 0;
            if (!checkbefore(line, counter))
                return (0);
            if (!checkafter(line, counter))
                return (0);
            while ((line[counter] == '|') && !ft_quotes(line, counter))
                counter++;
        }
        else
            counter++;
    }
    return (1);
}

int ft_pipe(char *line, t_shell *shell)
{
    (void)shell;
    if (!pipecheck(line))
    {
        printf("Syntaxe Error\n");
        free(line);
        return (0);
    }   
    return (1);
}