/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:47:21 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/23 00:00:39 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

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

bool	parse_n_flag(char **args, int *index)
{
	bool	the_n_flag;

	the_n_flag = false;
	while (args[*index] && is_there_n_falg(args[*index]))
	{
		the_n_flag = true;
		(*index)++;
	}
	return (the_n_flag);
}

void	print_arguments(char **args, int index)
{
	while (args[index])
	{
		ft_putstr_flag(args[index], false);
		if (args[index + 1])
			write(1, " ", 1);
		index++;
	}
}

int	echo_builtin(t_cmd *cmd)
{
	int		i;
	bool	the_n_flag;
	char	**args;
	char	exit_status_str[12];

	i = 0;
	args = cmd->args;
	the_n_flag = parse_n_flag(args, &i);
	print_arguments(args, i);
	if (!the_n_flag)
		write(1, "\n", 1);
	shell.exit = 0;
	return (0);
}
