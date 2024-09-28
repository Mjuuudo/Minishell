/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:27:36 by abait-ou          #+#    #+#             */
/*   Updated: 2024/09/28 18:49:52 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

void ft_freecmd(char *line, char **table)
{
    int counter;

    counter = 0;
    while (table[counter])
    {
        free(table[counter]);
        counter++;
    }
    free(table);
    free(line);
}