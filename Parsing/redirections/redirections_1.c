/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:00:36 by marvin            #+#    #+#             */
/*   Updated: 2024/12/18 14:16:36 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

int	ft_checkred(char **tab, char *cmd)
{
	int	i;

	if (!ft_strcmp(cmd, ">>") || !ft_strcmp(cmd, "<<") || !ft_strcmp(cmd, ">")
		|| !ft_strcmp(cmd, "<"))
	{
		return (1);
	}
	i = 0;
	while (tab[i])
	{
		if (!ft_strcmp(tab[i], ">>") || !ft_strcmp(tab[i], "<<")
			|| !ft_strcmp(tab[i], "<") || !ft_strcmp(tab[i], ">"))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_isredornot(char *tab)
{
	if (!ft_strcmp(tab, ">>") || !ft_strcmp(tab, "<<") || !ft_strcmp(tab, ">")
		|| !ft_strcmp(tab, "<"))
		return (1);
	else
		return (0);
}
