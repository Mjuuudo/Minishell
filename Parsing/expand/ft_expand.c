/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:41:53 by marvin            #+#    #+#             */
/*   Updated: 2024/12/18 15:09:44 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

int	indexdol(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (0);
}

void	ft_replace(t_token *token, t_envvar *env)
{
	if (ft_quotes(token->cmd, indexdol(token->cmd)))
	{
		if (isinornot(token->cmd, 0, 0, 0) == 2)
		{
			noquotes(token, env);
		}
		else
			return ;
	}
	else
		noquotes(token, env);
}

int	wordcount(char *str)
{
	int	counter;
	int	words;

	counter = 0;
	words = 0;
	while (isspace(str[counter]))
		counter++;
	if (str[counter] != '\0')
		words++;
	while (str[counter])
	{
		if (isspace(str[counter]))
		{
			while (isspace(str[counter]))
				counter++;
			if (str[counter] != '\0')
				words++;
		}
		counter++;
	}
	return (words);
}

int	ft_expand(t_token *token, t_envvar *env)
{
	if (ft_checkdollar(token->cmd))
	{
		ft_replace(token, env);
	}
	return (wordcount(token->cmd));
}

int	norm_3(int in_quotes)
{
	if (in_quotes == 1)
	{
		return (0);
	}
	else
		return (1);
}
