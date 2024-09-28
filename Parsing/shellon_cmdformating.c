/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellon_cmdformating.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:57:18 by abait-ou          #+#    #+#             */
/*   Updated: 2024/09/21 14:55:55 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

int ft_spacecalculation(char *line)
{
    int counter;
    int spaces;

    counter = 0;
    spaces = 0;
    while (line[counter])
    {
        if (line[counter] == '|' || line[counter] == '<' || line[counter] == '>')
            spaces++;
        if (line[counter + 1] == '>' && line[counter] == '>')
            counter++;
        else if (line[counter + 1] == '<' && line[counter] == '<')
            counter++;
        counter++;
    }
    return (spaces * 2);
}

