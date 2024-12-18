/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addnodecmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:44:17 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/18 15:48:50 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

void	ft_initnodecmd(t_token *node, char *value)
{
	node->cmd = ft_strdup(value);
	if (!ft_strncmp(value, "<", ft_strlen(value)))
		node->type = LESS;
	else if (!ft_strncmp(value, ">", ft_strlen(value)))
		node->type = GREAT;
	else if (!ft_strncmp(value, "<<", ft_strlen(value)))
		node->type = LLESS;
	else if (!ft_strncmp(value, ">>", ft_strlen(value)))
		node->type = DGREAT;
	else if (!ft_strncmp(value, "|", ft_strlen(value)))
		node->type = PIPE;
	else
		node->type = STR;
}

t_token	*ft_returnlastnodecmd(t_token *list)
{
	if (!list)
		return (NULL);
	while (list->next)
	{
		list = list->next;
	}
	return (list);
}

void	ft_morethan2(t_token *node, t_shell *shell, int counter)
{
	char	**holder;

	holder = ft_split(node->cmd, " \n\t\v\f\r");
	free(node->cmd);
	free(node);
	while (holder[counter] != NULL)
	{
		node = malloc(sizeof(t_token));
		if (!node)
			return ;
		node->next = NULL;
		ft_initnodecmd(node, holder[counter]);
		if (!shell->tokens)
		{
			shell->tokens = node;
			node->prev = NULL;
		}
		else
			norm_4(node);
		counter++;
	}
	counter = 0;
	while (holder[counter])
		free(holder[counter++]);
	free(holder);
}

void	ft_cmdliste(t_shell *shell, int counter)
{
	t_token	*node;
	t_token	*last_node;

	while (shell->commande.table[counter] != NULL)
	{
		node = malloc(sizeof(t_token));
		if (!node)
			return ;
		node->next = NULL;
		ft_initnodecmd(node, shell->commande.table[counter]);
		if (ft_expand(node, shell->envp) <= 1)
		{
			if (!shell->tokens)
			{
				shell->tokens = node;
				node->prev = NULL;
			}
			else
				norm_5(node);
			counter++;
		}
		else
			(ft_morethan2(node, shell, 0), counter++);
	}
}

void	ft_cmdliste_2(t_shell *shell, t_token *token)
{
	int	length;

	length = ft_nodescalculation(shell->tokens);
	while (length-- >= 0)
		token = ft_addnodecmd(shell, token);
}
