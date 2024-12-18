/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:27:36 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/18 11:34:54 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

static void	ft_freered(char **current)
{
	int	i;

	if (current)
	{
		i = 0;
		while (current[i])
			free(current[i++]);
		free(current);
	}
}

void	ft_freecmdmain(t_shell *shell)
{
	t_cmd			*current;
	t_redirection	*tmp;
	int				i;

	i = 0;
	current = shell->cmd;
	while (shell->cmd)
	{
		tmp = shell->cmd->red;
		while (tmp)
		{
			shell->cmd->red = shell->cmd->red->next;
			(free(tmp->file), free(tmp));
			tmp = shell->cmd->red;
		}
		shell->cmd = shell->cmd->next;
		free(current->order);
		while (current->args[i])
			free(current->args[i++]);
		free(current->args);
		ft_freered(current->red2);
		free(current);
		current = shell->cmd;
		i = 0;
	}
}

void	ft_freetokenmain(t_shell *shell)
{
	t_token	*current;

	current = shell->tokens;
	while (shell->tokens)
	{
		shell->tokens = shell->tokens->next;
		free(current->cmd);
		free(current);
		current = shell->tokens;
	}
}

void	ft_freefirstcmd(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->commande.table[i])
	{
		free(shell->commande.table[i]);
		i++;
	}
	free(shell->commande.table);
}
