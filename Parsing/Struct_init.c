/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:47:20 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/19 00:07:01 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

void	ft_members_init(t_shell *shell)
{
	shell->cmd = NULL;
	shell->tokens = NULL;
	shell->exit = 0;
}

int	norm_2(int in_quotes)
{
	if (in_quotes == 2)
	{
		return (0);
	}
	else
		return (2);
}

void	norm_4(t_token *node)
{
	t_token	*last_node;

	last_node = ft_returnlastnodecmd(shell.tokens);
	last_node->next = node;
	node->prev = last_node;
}

void	norm_5(t_token *node)
{
	t_token	*last_node;

	last_node = ft_returnlastnodecmd(shell.tokens);
	last_node->next = node;
	node->prev = last_node;
}

int	ft_videornor(char *line)
{
	int	counter;

	counter = 0;
	while (ft_ispace(line[counter]))
		counter++;
	if (line[counter] == '\0')
		return (1);
	return (0);
}
