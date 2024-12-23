/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 00:01:43 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/23 00:08:25 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"
#include <limits.h>
#include <stdbool.h>

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
	ft_malloc(0, 'f');
	exit(2);
}

void	free_env(t_envvar *env)
{
	t_envvar	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
	}
}

void	env_add_back(t_envvar **env, t_envvar *new)
{
	t_envvar	*tmp;

	if (!env || !new)
		return ;
	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
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
