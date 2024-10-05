/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputcorrection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:27:13 by abait-ou          #+#    #+#             */
/*   Updated: 2024/10/05 13:42:28 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"


char *spaced_string(char *line, t_shell *shell, int spaces, int counter_2)
{
    char  *spaced_string;
    int counter;
    
    spaced_string = malloc(sizeof(char) * (ft_strlen(line) + (spaces * 2 + 1)));
    if (!spaced_string)
        return (NULL);
    counter = 0;
    while (line[counter])
    {
        if ((line[counter] == '>' || line[counter] == '<' || line[counter] == '|')
                && !ft_quotes(line, counter))
        {
            spaced_string[counter_2++] = ' ';
            if (line[counter + 1] == '>' || line[counter + 1] == '<' 
                    || line[counter + 1] == '|')
                spaced_string[counter_2++] = line[counter++];
            spaced_string[counter_2++] = line[counter];
            spaced_string[counter_2++] = ' ';
        }
        else
            spaced_string[counter_2++] = line[counter];
        counter++;
    }
    spaced_string[counter_2] = '\0';
    return (spaced_string);
}

int count_spaces(char *line)
{
    int counter;
    int spaces;

    counter = 0;
    spaces  = 0;
    while (line[counter])
    {
        if (line[counter] == '|' || line[counter] == '<' || line[counter] == '>')
            spaces++;
        if (line[counter] && ((line[counter] =='>' && line[counter + 1] == '>')
                            || (line[counter] =='<' && line[counter + 1] == '<'))) 
            spaces--;
        counter++;
    }
    return (spaces);
}