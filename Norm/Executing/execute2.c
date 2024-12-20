/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:13:21 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/20 22:42:22 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

bool	execute_builtin(t_cmd *cmd)
{
	int			i;
	static char	*builtins[8];

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	static int (*builtin_functions[])(t_cmd *) = {echo_builtin, cd_builtin,
		pwd_builtin, export_builtin, unset_builtin, env_builtin, exit_builtin};
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

int	execute_without_path(t_cmd *cmd)
{
	char	**args;
	int		i;

	i = 0;
	// args = parse_and_handle_redirection(&shell);
	// join_order_with_args(cmd, args);
	args = construct_args(cmd);
	if (access(cmd->order, F_OK) != 0)
	{
		fprintf(stderr, "minishell$: %s: No such file or directory\n",
			cmd->order);
		ft_malloc(0, 'f');
		exit(127);
	}
	if (access(cmd->order, X_OK) != 0)
	{
		fprintf(stderr, "minishell$: %s: Permission denied\n", cmd->order);
		ft_malloc(0, 'f');
		exit(126);
	}
	execve(cmd->order, args, shell.envholder);
	perror("minishell$");
	ft_malloc(0, 'f');
	exit(1);
}

static bool is_redirection_char(char c)
{
 	return (c == '>' || c == '<');
}

static void check_order0(t_cmd *cmd)
{
	if (!cmd->order || !cmd->order[0])
	{
		ft_malloc(0, 'f');
		exit(0);
	}

	if (is_redirection_char(cmd->order[0]))
	{
		if (cmd->order[1] && is_redirection_char(cmd->order[1]))
			exit(0);
		exit(0);
	}
}

int execute_with_path(t_cmd *cmd)
{
	char	*path;
	char	**args;

	check_order0(cmd);
	path = making_the_path(cmd);
	// path = NULL;  //TODO.
	if (path == NULL)
	{
		fprintf(stderr, "minishell04$: command not found: %s\n", cmd->order);
		// ft_freeenv(shell.envp);
		// ft_freeenvholder(shell.envholder);
		// ft_freecmdmain(&shell);
		ft_malloc(0, 'f');
		exit(127);
	}
	// args = parse_and_handle_redirection(&shell);
	// join_order_with_args(cmd, args);
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

void cleanup_and_exit(int status)
{
	ft_freeenv(shell.envp);
	ft_freeenvholder(shell.envholder);
	ft_freecmdmain(&shell);
	exit(status);
}
