/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:47:21 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/08 16:11:32 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

/**
 * ?===========================Improvement===============================?
 * ?Improvement: You can optimize this function by using strlen()
 * ?and writing the entire string in one go instead of character by character,
 * ?reducing the number of system calls:
 */

void	ft_putstr_flag(char *str, bool n_flag)
{
	while (*str != '\0')
	{
		write(1, str, 1);
		str++;
	}
	if (n_flag)
		write(1, "\n", 1);
}

static bool	is_there_n_falg(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (false);
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	echo_builtin(t_cmd *cmd)
{
	int		i;
	bool	the_n_flag;
	char	**args;

	i = 0;
	the_n_flag = false;
	args = cmd->args;
	/**
	 *=*=======*Check for -n flags*========*
	 */
	while (args[i] && is_there_n_falg(args[i]))
	{
		the_n_flag = true;
		i++;
	}
	/**
	 *=*=======*Print the arguments*========*
	 */
	while (args[i])
	{
		ft_putstr_flag(args[i], false);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!the_n_flag)
		write(1, "\n", 1);
	
	return (0);
}

