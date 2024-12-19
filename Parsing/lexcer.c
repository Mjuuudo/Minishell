/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:35:03 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/19 13:16:00 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

void	ft_parser(t_shell *shell)
{
	ft_cmdliste(shell, 0);
	ft_cmdliste_2(shell, shell->tokens);
	ft_freetokenmain(shell);
}

static void	ft_lexcer(char *line, t_shell *shell)
{
	int	length;

	length = count_spaces(line);
	shell->commande.commande = spaced_string(line, shell, length, 0);
	free(line);
	shell->commande.table = ft_split(shell->commande.commande, " \n\t\v\f\r");
	free(shell->commande.commande);
}

void	ft_cmdhandler(char *line, t_shell *shell)
{
	if (ft_quotesch(line, shell) && ft_pipe(line, shell)
		&& ft_redirections(line, shell))
	{
		ft_lexcer(line, shell);
		ft_parser(shell);
		ft_freefirstcmd(shell);
	}
}

void ft_exitstatus(char *line, int *i, char *new_string)
{
	char	*status;
	int		j;

	status = ft_itoa(shell.exit);
	j = 0;
	while (status[j])
		new_string[shell.counter++] = status[j++];
	free(status);
	(*i)++;
}
