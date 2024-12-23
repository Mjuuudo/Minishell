/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:27:36 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/23 00:38:19 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

void	ft_freecmdmain(g_shell *shell)
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
			tmp = shell->cmd->red;
		}
		shell->cmd = shell->cmd->next;
		current = shell->cmd;
		i = 0;
	}
}

void	ft_freetokenmain(g_shell *shell)
{
	t_token	*current;

	current = shell->tokens;
	while (shell->tokens)
	{
		shell->tokens = shell->tokens->next;
		current = shell->tokens;
	}
}

void	ft_freefirstcmd(g_shell *shell)
{
	int	i;

	i = 0;
	while (shell->commande.table[i])
		i++;
}
