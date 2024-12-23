/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:41:53 by marvin            #+#    #+#             */
/*   Updated: 2024/12/22 15:12:34 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

void	init_replace_vars(t_replace *vars, t_token *token)
{
	vars->str = token->cmd;
	vars->i = 0;
	vars->in_single_quotes = 0;
	vars->in_double_quotes = 0;
	vars->counter = 0;
	vars->new_string = ft_malloc(sizeof(char) * (ft_strlen(vars->str) * 100),
			'm');
}

int	handle_quotes(t_replace *vars)
{
	if (vars->str[vars->i] == '\'' && !vars->in_double_quotes)
	{
		vars->in_single_quotes = !vars->in_single_quotes;
		vars->new_string[vars->counter++] = vars->str[vars->i++];
		return (1);
	}
	if (vars->str[vars->i] == '"' && !vars->in_single_quotes)
	{
		vars->in_double_quotes = !vars->in_double_quotes;
		vars->new_string[vars->counter++] = vars->str[vars->i++];
		return (1);
	}
	return (0);
}

void	handle_char(t_replace *vars)
{
	if (vars->str[vars->i] == '$' && !vars->in_single_quotes)
		handle_dollar_sign(vars->str, vars->new_string, &vars->i,
			&vars->counter);
	else
		vars->new_string[vars->counter++] = vars->str[vars->i++];
}
