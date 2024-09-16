/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:22:37 by abait-ou          #+#    #+#             */
/*   Updated: 2024/09/16 16:39:14 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"


char *ft_strncpy(char *dst, char *src, unsigned int len)
{
    int counter;

    counter = 0;
    if (len == 0)
        return (dst);
    while (src[counter] && counter < len)
    {
        dst[counter] = src[counter];
        counter++;
    }
    return (dst);
}