/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:19:02 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/19 13:08:57 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"
#include <limits.h>
#include <stdbool.h>

bool	is_valid_number(const char *str)
{
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
		|| *str == '\v' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (false);
	while (*str != '\0')
	{
		if (!(*str >= '0' && *str <= '9'))
			return (false);
		str++;
	}
	return (true);
}

int	normalize_exit_status(int exit_status)
{
	if (exit_status < 0)
		exit_status = (exit_status + 256);
	else if (exit_status > 255)
		exit_status = exit_status % 256;
	shell.exit = exit_status;
	return (exit_status);
}

static unsigned char	ft_atouc(const char *av)
{
	int	res;

	res = 0;
	while (*av >= '0' && *av <= '9')
		res = res * 10 + (*av++ - '0');
	return ((unsigned char)res);
}

int	handle_overflowing_number(const char *arg)
{
	char	*buffer;

	printf("exit2\n");
	buffer = ft_strjoin("minishell11: exit: ", arg);
	if (buffer)
	{
		write(2, buffer, ft_strlen(buffer));
		write(2, ": numeric argument required\n", 28);
		free(buffer);
	}
	shell.exit = 2;
	return (2);
}

int	handle_too_many_arguments(void)
{
	printf("exit\n");
	printf("exit: too many arguments\n");
	shell.exit = 1;
	return (1);
}

int	handle_non_numeric_argument(const char *arg)
{
	printf("exit\n");
	printf("exit: numeric argument required\n");
	shell.exit = 2;
	return (2);
}

int	exit_builtin(t_cmd *cmd)
{
	unsigned char	exit_status;

	if (cmd->args[0] == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	if (!is_valid_number(cmd->args[0]))
		return (handle_non_numeric_argument(cmd->args[0]));
	if (is_valid_number(cmd->args[0]) && cmd->args[1])
		return (handle_too_many_arguments());
	if (cmd->args[0])
	{
		if (ll_max_check(cmd->args[0]))
			return (handle_overflowing_number(cmd->args[0]));
		exit_status = (unsigned char)ft_atouc(cmd->args[0]);
	}
	else
		exit_status = shell.exit;
	shell.exit = normalize_exit_status(exit_status);
	exit(shell.exit);
}

int	ll_max_check(char *str)
{
	long long int	status;
	int				sign;
	int				i;

	status = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (str && str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (status > LLONG_MAX / 10 || (status == LLONG_MAX / 10 && (str[i]
					- '0') > LLONG_MAX % 10))
		{
			if (sign == -1 && status == LLONG_MAX / 10 && str[i] == '8' && str[i
				+ 1] == '\0')
				return (0);
			if (sign == 1 || (sign == -1 && status > LLONG_MAX / 10))
				return (1);
			return (1);
		}
		status = status * 10 + (str[i++] - '0');
	}
	return (0);
}
