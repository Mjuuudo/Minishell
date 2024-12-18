/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:57:29 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/18 15:29:22 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

int	ft_ispace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}
