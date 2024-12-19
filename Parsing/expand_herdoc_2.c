/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_herdoc_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:12:14 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/19 13:15:51 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

char	*replace_env_var(t_envvar *env, char *holder, char *new_string)
{
	char	*value;
	int		j;

	value = retrivevalueher(env, holder);
	j = 0;
	while (value && value[j])
		new_string[shell.counter++] = value[j++];
	free(value);
	return (NULL);
}

char	*process_dollar_token(char *line, char *new_string, int *i, int *j)
{
	char	holder[1024];
	int		len;
	char	*result;

	if (ft_isalpha(line[*i]) || line[*i] == '_')
	{
		len = read_var_name(line, i, holder);
		if (len > 0 && !foundornother(holder, shell.envp))
			return (NULL);
		result = replace_env_var(shell.envp, holder, new_string);
		if (result)
		{
			new_string[shell.counter++] = result[(*j)++];
			*j = 0;
		}
	}
	else if(line[*i] == '?')
		ft_exitstatus(line, i, new_string);
	else
	{
		new_string[shell.counter++] = '$';
		if (line[*i])
			new_string[shell.counter++] = line[(*i)++];
	}
	return (new_string);
}

char	*noquotesher(char *line, t_envvar *env, int i, int j)
{
	char	*new_string;

	shell.counter = 0;
	new_string = malloc(sizeof(char) * (ft_strlen(line) * 500));
	if (!new_string)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			if (!process_dollar_token(line, new_string, &i, &j))
				break ;
		}
		else
			new_string[shell.counter++] = line[i++];
	}
	new_string[shell.counter] = '\0';
	free(line);
	return (new_string);
}

char	*ft_replaceher(char *line, t_envvar *env)
{
	return (noquotesher(line, env, 0, 0));
}

char	*ft_expandherdoc(char *line, t_envvar *env)
{
	char	*new_line;

	if (ft_checkdollarher(line))
	{
		line = ft_replaceher(line, env);
	}
	return (line);
}
