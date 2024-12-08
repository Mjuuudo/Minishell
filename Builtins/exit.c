/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:19:02 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/07 21:48:12 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"
# include <limits.h>
# include <stdbool.h>

bool is_valid_number(const char *str)
{
	printf("str: %s\n", str);
    // Skip leading whitespace
	while(*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\r' || *str == '\v' || *str == '\f')
		str++;
    // Check for sign
	if(*str == '-' || *str == '+')
		str++;
    // Check for empty string or just a sign
	if(*str == '\0')
		return(false);
	while(*str != '\0')
	{
		if (!(*str >= '0' && *str <= '9'))
			return(false);
		str++;
	}
	return(true);
}
int normalize_exit_status(int exit_status)
{
	if(exit_status < 0)
		exit_status = (exit_status + 256);
	else if(exit_status > 255)
		exit_status = exit_status % 256;
	return(exit_status);
}

static	unsigned char	ft_atouc(const char *av)
{
	int	res = 0;
	while(*av >= '0' && *av <= '9')
		res = res * 10 + (*av++ - '0');
	// printf("res ===>%d\n", res);
	return((unsigned char)res);
}

int exit_builtin(t_cmd *cmd)
{
	printf("here2\n");
	// printf("cmd->args[0]: %s\n", shell->cmd->args[0]);
    unsigned char exit_status;

    // if (shell->cmd->args[0] && cmd->args[1])
    // {
    //     if (is_valid_number(cmd->args[1]) && is_valid_number(cmd->args[2]))
    //     {
    //         printf("exit: too many arguments\n");
    //         exit_status = 1;
    //     }
    //     else if (is_valid_number(cmd->args[1]) && !is_valid_number(cmd->args[2]))
    //     {
    //         printf("exit: too many arguments\n");
    //         exit_status = 1;
    //     }
    //     else if (!is_valid_number(cmd->args[1]) && is_valid_number(cmd->args[2]))
    //     {
    //         printf("exit: numeric argument required\n");
    //         exit_status = 2;
    //         exit(2);
    //     }
    //     else if (!is_valid_number(cmd->args[1]) && !is_valid_number(cmd->args[2]))
    //     {
    //         printf("exit: numeric argument required\n");
    //         exit_status = 2;
    //         exit(2);
    //     }
    // }
	printf("here3\n");
	printf("cmd->args[0]: %s\n", cmd->args[0]);
    if (cmd->args[0])
    {
		printf("here4\n");
        if (!is_valid_number(cmd->args[0]))
        {
            printf("exit: numeric argument required\n");
            exit_status = 2;
            exit(2);
        }
		printf("here5\n");
        exit_status = (unsigned char)ft_atouc(cmd->args[0]);
		printf("exit_status: %d\n", exit_status);
    }
    else
        exit_status = shell.exit;  // Use shell->exit (last_exit_status)
    exit(normalize_exit_status(exit_status));
}

