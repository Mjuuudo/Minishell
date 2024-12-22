/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_norms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:20:56 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/22 12:46:30 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

void	ft_norm6(t_cmd **node, t_token *token, int *counter, int *length)
{
	if (!ft_strcmp(token->cmd, "$?"))
	{
		(*node)->order = ft_itoa(shell.exit);
		token = token->next;
	}
	else
		(*node)->order = ft_strdup(token->cmd);
}

void	ft_norm7(t_cmd **node, t_token *token, int *counter, int *length)
{
	if (!ft_strcmp(token->cmd, "$?"))
	{
		(*node)->args[*length] = ft_itoa(shell.exit);
		(*length)++;
		token = token->next;
	}
	else
	{
		(*node)->args[*length] = ft_strdup(token->cmd);
		(*length)++;
	}
}

int	ft_norm8(t_token *token)
{
	if ((token->type == GREAT || token->type == DGREAT || token->type == LESS
			|| token->type == LLESS) || (token->prev->type == GREAT
			|| token->prev->type == DGREAT || token->prev->type == LESS
			|| token->prev->type == LLESS))
		return (1);
	return (0);
}

t_token	*ft_norm9(t_cmd **node, t_token *token, int *counter, int *length)
{
	ft_norm6(node, token, counter, length);
	token = token->next;
	return (token);
}

t_token	*ft_norm10(t_cmd **node, t_token *token, int *counter, int *length)
{
	ft_norm7(node, token, counter, length);
	token = token->next;
	return (token);
}
