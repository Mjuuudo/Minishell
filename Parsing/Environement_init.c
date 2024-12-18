/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Environement_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:49:00 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/18 14:14:17 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

t_envvar	*ft_environementinit(t_envvar *envliste, char **env)
{
	int	counter;

	counter = 0;
	envliste = NULL;
	while (env[counter])
		ft_addnodeenv(&envliste, env[counter++]);
	return (envliste);
}

static int	ft_envlength(char **env)
{
	int	length;

	length = 0;
	while (env[length])
		length++;
	return (length);
}

char	**ft_envholder(char **env, t_shell *shell)
{
	int		counter;
	char	**new_array;

	(void)shell;
	new_array = (char **)malloc(sizeof(char *) * (ft_envlength(env) + 1));
	if (!new_array)
		return (NULL);
	counter = 0;
	while (env[counter])
	{
		new_array[counter] = ft_strdup(env[counter]);
		counter++;
	}
	new_array[counter] = NULL;
	return (new_array);
}
