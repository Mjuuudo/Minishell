/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:50:34 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/23 00:34:38 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"
#define PATH_MAX 1024

int	ft_quotes(char *line, int index)
{
	int		counter;
	char	sym;
	int		start;
	int		end;

	counter = 0;
	while (line[counter])
	{
		if (line[counter] == 39 || line[counter] == '"')
		{
			start = counter;
			sym = line[counter++];
			while (line[counter] != sym && line[counter])
				counter++;
			end = counter;
			if (start <= index && end >= index)
				return (1);
		}
		counter++;
	}
	return (0);
}

void	fg_shell_on(g_shell *shell)
{
	char	*line;
	int		i;

	i = 0;
	signal(SIGQUIT, SIG_IGN);
	while (true)
	{
		signal(SIGINT, handler);
		line = readline("Blackhole_Lover's@Minis(hell):~$ ");
		signal(SIGINT, SIG_IGN);
		if (!line)
			break ;
		if (!*line || ft_videornor(line))
			continue ;
		add_history(line);
		if (ft_quotesch(line, shell) && ft_pipe(line, shell)
			&& ft_redirections(line, shell))
		{
			ft_cmdhandler(line, shell);
			implement_heredoc(shell->cmd);
			ft_execution(shell->cmd);
			ft_freecmdmain(shell);
		}
	}
	(ft_malloc(0, 'f'), printf("exit\n"));
}
