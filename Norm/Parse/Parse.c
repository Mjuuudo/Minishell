/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:08:32 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/20 11:35:40 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"


int count_commands_and_flags(t_cmd *cmd)
{
    int count = 1; // Start with 1 for the command itself
    int i = 0;

    while (cmd->args[i] != NULL)
    {
        // Skip redirection symbols
        if (strcmp(cmd->args[i], "<") != 0 && strcmp(cmd->args[i], "<<") != 0 &&
            strcmp(cmd->args[i], ">") != 0 && strcmp(cmd->args[i], ">>") != 0)
        {
            count++;
        }
        i++;
    }
    return count;
}

// Function to construct the args array for execve
char **construct_args(t_cmd *cmd)
{
    int count = count_commands_and_flags(cmd);
    char **args = malloc(sizeof(char *) * (count + 1)); // +1 for NULL terminator
    int i = 0, j = 1; // j starts at 1 to reserve args[0] for the command

    if (!args)
    {
        perror("malloc failed");
        exit(1);
    }

    args[0] = strdup(cmd->order); // Copy the command
    if (!args[0])
    {
        perror("strdup failed");
        free(args);
        exit(1);
    }

    while (cmd->args[i] != NULL)
    {
        // Skip redirection symbols
        if (strcmp(cmd->args[i], "<") != 0 && strcmp(cmd->args[i], "<<") != 0 &&
            strcmp(cmd->args[i], ">") != 0 && strcmp(cmd->args[i], ">>") != 0)
        {
            args[j] = ft_strdup(cmd->args[i]); // Copy each valid argument
            if (!args[j])
            {
                perror("strdup failed");
                for (int k = 0; k < j; k++)
                    free(args[k]);
                free(args);
                exit(1);
            }
            j++;
        }
        i++;
    }
    args[j] = NULL; // NULL terminate the array
    return args;
}

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
	int		arg_count;
	char	**only_args;

	arg_count = count_commands_anf_flags(shell);
	only_args = malloc(sizeof(char *) * (arg_count + 2));
	if (!only_args)
		return (NULL);
	only_args = copy_command_and_flags(shell, only_args);
	return (only_args);
}
