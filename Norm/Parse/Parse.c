/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:08:32 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/23 00:19:44 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

int	count_commands_and_flags(t_cmd *cmd)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (cmd->args[i] != NULL)
	{
		if (strcmp(cmd->args[i], "<") != 0 && strcmp(cmd->args[i], "<<") != 0
			&& strcmp(cmd->args[i], ">") != 0 && strcmp(cmd->args[i],
				">>") != 0)
		{
			count++;
		}
		i++;
	}
	return (count);
}

char	**construct_args(t_cmd *cmd)
{
	char	**args;

	int (count), (i), (j);
	count = count_commands_and_flags(cmd);
	args = ft_malloc(sizeof(char *) * (count + 1), 'm');
	i = -1;
	j = 1;
	if (!args)
		(perror("strdup failed"), ft_malloc(0, 'f'), exit(1));
	args[0] = ft_strdup(cmd->order);
	if (!args[0])
		(perror("strdup failed"), ft_malloc(0, 'f'), exit(1));
	while (cmd->args[++i] != NULL)
	{
		if (strcmp(cmd->args[i], "<") != 0 && strcmp(cmd->args[i], "<<") != 0
			&& strcmp(cmd->args[i], ">") != 0 && strcmp(cmd->args[i],
				">>") != 0)
		{
			args[j] = ft_strdup(cmd->args[i]);
			if (!args[j])
				(perror("strdup failed"), ft_malloc(0, 'f'), exit(1));
			j++;
		}
	}
	return (args[j] = NULL, args);
}

int	count_commands_anf_flags(g_shell *shell)
{
	int	i;
	int	arg_count;

	arg_count = 0;
	i = 0;
	while (shell->cmd->args[i] != NULL)
	{
		if (strcmp(shell->cmd->args[i], "<") != 0 && strcmp(shell->cmd->args[i],
				"<<") != 0 && strcmp(shell->cmd->args[i], ">") != 0
			&& strcmp(shell->cmd->args[i], ">>") != 0 && (i == 0
				|| (strcmp(shell->cmd->args[i - 1], "<") != 0
					&& strcmp(shell->cmd->args[i - 1], "<<") != 0
					&& strcmp(shell->cmd->args[i - 1], ">") != 0
					&& strcmp(shell->cmd->args[i - 1], ">>") != 0)))
		{
			arg_count++;
		}
		i++;
	}
	return (arg_count);
}

char	**copy_command_and_flags(g_shell *shell, char **only_args)
{
	int	arg_index;
	int	i;

	arg_index = 0;
	i = 0;
	only_args[arg_index++] = ft_strdup(shell->cmd->order);
	while (shell->cmd->args[i] != NULL)
	{
		if (strcmp(shell->cmd->args[i], "<") != 0 && strcmp(shell->cmd->args[i],
				"<<") != 0 && strcmp(shell->cmd->args[i], ">") != 0
			&& strcmp(shell->cmd->args[i], ">>") != 0 && (i == 0
				|| (strcmp(shell->cmd->args[i - 1], "<") != 0
					&& strcmp(shell->cmd->args[i - 1], "<<") != 0
					&& strcmp(shell->cmd->args[i - 1], ">") != 0
					&& strcmp(shell->cmd->args[i - 1], ">>") != 0)))
		{
			only_args[arg_index++] = ft_strdup(shell->cmd->args[i]);
		}
		i++;
	}
	only_args[arg_index] = NULL;
	return (only_args);
}

char	**parse_and_handle_redirection(g_shell *shell)
{
	int		arg_count;
	char	**only_args;

	arg_count = count_commands_anf_flags(shell);
	only_args = ft_malloc(sizeof(char *) * (arg_count + 2), 'm');
	if (!only_args)
		return (NULL);
	only_args = copy_command_and_flags(shell, only_args);
	return (only_args);
}
