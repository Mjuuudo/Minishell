/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:47:58 by abait-ou          #+#    #+#             */
/*   Updated: 2024/10/17 13:13:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

static int checkredirectionum(char *line, int counter)
{
    if (line[counter] == '>')
    {
        if (line[counter + 1] == '>')
        {
            if (line[counter + 2] == '>')
                return (0);
        }
    }
     if (line[counter] == '<')
    {
        if (line[counter + 1] == '<')
        {
            if (line[counter + 2] == '<')
            {
                if (line[counter + 3] == '<')
                    return (0);
            }
        }
    }
    return (1);
}
static int checkbefore(char *line, int counter)
{
    while (counter-- > 0)
    {
        if (!ft_ispace(line[counter]) && line[counter] != '\0')
        {
            if (line[counter] == '>' || line[counter] == '<')
                return (0);
            else
                return (1); 
        } 
    }
    return (0);
}
static int checkafter(char *line, int counter)
{
    while (line[counter] == '>' || line[counter] == '<')
        counter++;
    while (line[counter])
    {
        if (!ft_ispace(line[counter]) && line[counter] != '\0')
        {
            if (line[counter] == '>' || line[counter] == '<')
                return (0);
            else
                return (1); 
        } 
        counter++;
    }
    return (0);
}


static int redirectioncheck(char *line)
{
    int counter;
    int status;

    counter = 0;
    while (line[counter])
    {
        if ((line[counter] == '>' || line[counter] == '<') 
                                && !ft_quotes(line, counter))
        {
            if (!checkredirectionum(line, counter))
                return (0);
            if (!checkbefore(line, counter))
                return (0);
            if (!checkafter(line, counter))
                return (0);
            while ((line[counter] == '>' || line[counter] == '<') 
                                && !ft_quotes(line, counter))
                counter++;
        }
        else
            counter++; 
    }
    return (1);
}

int ft_redirections(char *line, t_shell *shell)
{
    if (!redirectioncheck(line))
    {
        printf("Syntaxe Error\n");
        free(line);
        return (0);
    }    
    return (1);
}