/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:08:49 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/20 22:53:38 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

static void	ft_bzero(void *dst, size_t n)
{
	size_t	compteur;

	compteur = 0;
	while (compteur < n)
	{
		((char *)dst)[compteur] = 0;
		compteur++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t the_size;
	void *ptr;

	if (nmemb == 0 || size == 0)
	{
		ptr = malloc(1);
		ft_bzero(ptr, 1);
		return (ptr);
	}
	the_size = nmemb * size;
	if (the_size / nmemb != size)
		return (NULL);
	// ptr = malloc(the_size);
	ptr = ft_malloc(the_size, 'm');
	if (ptr != NULL)
	{
		ft_bzero(ptr, the_size);
	}
	return (ptr);
}
