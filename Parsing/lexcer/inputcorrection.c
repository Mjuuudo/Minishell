/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputcorrection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:27:13 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/11 13:18:07 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"


char *spaced_string(char *line, t_shell *shell, int spaces, int counter_2)
{
    size_t line_len = ft_strlen(line);
    char *spaced_string ;
    // Allocate more space to be safe - worst case is if every character needs spacing
    size_t max_possible_len = line_len + (line_len * 2) + 1;  
    

    spaced_string = malloc(max_possible_len);
    if (!spaced_string)
        return (NULL);
    
    size_t counter = 0;
    size_t write_index = 0;
    while (line[counter])
    {
        // Ensure we don't overflow the buffer
        if (write_index >= max_possible_len - 2) {
            free(spaced_string);
            return (NULL);
        }
        if ((line[counter] == '>' || line[counter] == '<' || line[counter] == '|')
                && !ft_quotes(line, counter))
        {
            spaced_string[write_index++] = ' ';
            
            if (line[counter + 1] == '>' || line[counter + 1] == '<' 
                    || line[counter + 1] == '|')
                spaced_string[write_index++] = line[counter++];
            
            spaced_string[write_index++] = line[counter];
            spaced_string[write_index++] = ' ';
        }
        // else if (line[counter] == '$')
        // {
        //     spaced_string[write_index++] = ' ';
        //     spaced_string[write_index++] = line[counter];
        // }
        else
            spaced_string[write_index++] = line[counter];
        counter++;
    }
    spaced_string[write_index] = '\0';
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