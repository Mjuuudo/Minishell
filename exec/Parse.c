/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:08:32 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/16 23:39:08 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

int	count_commands_anf_flags(t_shell *shell)
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
	// printf("arg_count: %d\n", arg_count);
	return (arg_count);
}

char	**copy_command_and_flags(t_shell *shell, char **only_args)
{
	int	arg_index;
	int	i;

	arg_index = 0;
	i = 0;
	only_args[arg_index++] = strdup(shell->cmd->order);

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
			only_args[arg_index++] = strdup(shell->cmd->args[i]);
		}
		i++;
	}
	only_args[arg_index] = NULL;
	return (only_args);
}

char	**parse_and_handle_redirection(t_shell *shell)
{
	int		arg_count = 0;
	char	**only_args = NULL;

	arg_count = count_commands_anf_flags(shell);
	// printf("arg_count: %d\n", arg_count);
	only_args = malloc(sizeof(char *) * (arg_count + 2));
	only_args = copy_command_and_flags(shell, only_args);
	return (only_args);
}
