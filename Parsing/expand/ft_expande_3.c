/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expande_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:30:39 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/23 01:53:54 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

void	noquotes(t_token *token, t_envvar *env)
{
	char	*new_string;
	int		new_len;
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	new_len = ft_strlen(token->cmd) * 100;
	new_string = ft_malloc(sizeof(char) * new_len, 'm');
	if (!new_string)
		return ;
	while (token->cmd[i])
	{
		if (token->cmd[i] == '$')
		{
			if (!handle_dollar_sign(token->cmd, new_string, &i, &counter))
				break ;
		}
		else
			new_string[counter++] = token->cmd[i++];
	}
	new_string[counter] = '\0';
	token->cmd = new_string;
}

int	handle_dollar_sign(char *input, char *new_string, int *i, int *counter)
{
	char	holder[1024];

	int (var_len), (j);
	(*i)++;
	j = 0;
	if (!is_valid_var_start(input[*i]))
	{
		new_string[(*counter)++] = '$';
		if (input[*i])
			new_string[(*counter)++] = input[(*i)++];
		return (1);
	}
	var_len = extract_var_name(input, holder, i);
	if (var_len == 0)
	{
		new_string[(*counter)++] = '$';
		return (1);
	}
	if (!handle_env_var(new_string, holder, shell.envp, counter))
	{
		new_string[(*counter)++] = '$';
		while (j < var_len)
			new_string[(*counter)++] = holder[j++];
	}
	return (1);
}
