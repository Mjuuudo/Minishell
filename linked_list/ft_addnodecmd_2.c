/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addnodecmd_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:20:56 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/18 15:49:40 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

int	ft_arcal(t_token *tokens)
{
	int	length;

	length = 0;
	while (tokens)
	{
		if (tokens->type == PIPE)
			break ;
		if ((tokens->type == GREAT || tokens->type == DGREAT
				|| tokens->type == LESS || tokens->type == LLESS))
		{
			tokens = tokens->next->next;
			continue ;
		}
		length++;
		tokens = tokens->next;
	}
	return (length);
}

int	redcalcu(t_token *tokens)
{
	int	length;

	length = 0;
	while (tokens)
	{
		if (tokens->type == PIPE)
			break ;
		if ((tokens->type == GREAT || tokens->type == DGREAT
				|| tokens->type == LESS || tokens->type == LLESS))
			length += 2;
		tokens = tokens->next;
	}
	return (length);
}

t_token	*ft_nodecmdinit(t_cmd **node, t_token *token, int counter, int length)
{
	(*node)->args = (char **)malloc(sizeof(char *) * (ft_arcal(token) + 2));
	(*node)->red2 = (char **)malloc(sizeof(char *) * (redcalcu(token) + 2));
	while (token)
	{
		if (token->type == PIPE)
		{
			token = token->next;
			break ;
		}
		else if (!token->prev || (token->prev->type == PIPE && token))
			((*node)->order = ft_strdup(token->cmd), token = token->next);
		else if ((token->type == GREAT || token->type == DGREAT
				|| token->type == LESS || token->type == LLESS)
			|| (token->prev->type == GREAT || token->prev->type == DGREAT
				|| token->prev->type == LESS || token->prev->type == LLESS))
			((*node)->red2[counter++] = ft_strdup(token->cmd),
				token = token->next);
		else if (token->prev || token->prev->type != PIPE)
			((*node)->args[length++] = ft_strdup(token->cmd),
				token = token->next);
	}
	(*node)->args[length] = NULL;
	(*node)->red2[counter] = NULL;
	return (token);
}
// here

t_token	*ft_addnodecmd(t_shell *shell, t_token *token)
{
	t_cmd	*node;
	t_cmd	*last_node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->next = NULL;
	token = ft_nodecmdinit(&node, token, 0, 0);
	ft_redirectioninit(&node, 0);
	ft_quotesremove(&node);
	if (!(shell->cmd))
	{
		(shell->cmd) = node;
		node->prev = NULL;
	}
	else
	{
		last_node = ft_returnlastnodecmd2((shell->cmd));
		last_node->next = node;
		node->prev = last_node;
	}
	return (token);
}

int	ft_nodescalculation(t_token *token)
{
	int		length;
	t_token	*tokens;

	length = 0;
	tokens = token;
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			length++;
			if (token->next->type == PIPE)
				token = token->next;
		}
		tokens = tokens->next;
	}
	return (length);
}
