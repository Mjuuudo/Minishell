/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:59:26 by abait-ou          #+#    #+#             */
/*   Updated: 2024/09/16 16:59:52 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../Includes/Minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	compteur;

	compteur = 0;
	while (str[compteur])
	{
		compteur++;
	}
	return (compteur);
}
