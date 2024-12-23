/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:13:21 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/22 23:07:09 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

void	initilized(char **builtins)
{
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
}

bool	execute_builtin(t_cmd *cmd)
{
	int			i;
	static char	*builtins[8];
	static int	(*builtin_functions[])(t_cmd *) = {echo_builtin, cd_builtin,
		pwd_builtin, export_builtin, unset_builtin, env_builtin, exit_builtin};

	initilized(builtins);
	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(cmd->order, builtins[i]) == 0)
		{
			if (!set_redirections(cmd->red))
				return (reset_redirections(), false);
			builtin_functions[i](cmd);
			reset_redirections();
			return (true);
		}
		i++;
	}
	return (false);
}

static void	check_order0(t_cmd *cmd)
{
	if (!cmd->order || !cmd->order[0])
	{
		ft_malloc(0, 'f');
		exit(0);
	}
	if (cmd->order[0] == '>' || cmd->order[0] == '<')
	{
		if (cmd->order[1] && (cmd->order[1] == '>' || cmd->order[1] == '<'))
			exit(0);
		exit(0);
	}
}

int	execute_with_path(t_cmd *cmd)
{
	char	*path;
	char	**args;

	check_order0(cmd);
	path = making_the_path(cmd);
	if (path == NULL)
	{
		fprintf(stderr, "minishell04$: command not found: %s\n", cmd->order);
		ft_malloc(0, 'f');
		exit(127);
	}
	args = construct_args(cmd);
	if (execve(path, args, shell.envholder) == -1)
	{
		perror("execve failed");
		ft_malloc(0, 'f');
		exit(1);
	}
	ft_malloc(0, 'f');
	exit(1);
}
