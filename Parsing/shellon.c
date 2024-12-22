/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:50:34 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/22 12:47:27 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"
#define PATH_MAX 1024

int ft_quotes(char *line, int index)
{
    int counter;
    char sym;
    int start;
    int end;

    counter = 0;
    while (line[counter])
    {
        if (line[counter] == 39 || line[counter] == '"')
        {
            start = counter;
            sym = line[counter++];
            while(line[counter] != sym && line[counter])
                counter++;
            end = counter;
             if (start <= index && end >= index)
                return (1);
        }
        counter++;
    }
    return (0);
}

static void display_cmd(t_shell *shell)
{
    int i = 0;
    while (shell->cmd)
    {
        printf("arg cmd [ ] %s\n", shell->cmd->order);
        while (shell->cmd->args[i])
        {
                printf("-->  args [%d] %s\n", i, shell->cmd->args[i]);
                i++;
        }
        i = 0;
		while (shell->cmd->red2[i])
        {
                printf("-->  redirection in red 2 [%d] %s\n", i, shell->cmd->red2[i]);
                i++;
        }
		i = 0;
        printf("---------- Redirections -------------\n");
        while (shell->cmd->red)
        {

            printf ("File %s, Type %d\n", shell->cmd->red->file, shell->cmd->red->identifier);
            shell->cmd->red = shell->cmd->red->next;
        }
        printf("------------ End Redirection -----------\n");
        shell->cmd = shell->cmd->next;
    }
}


void ft_shell_on(t_shell *shell)
{
	char *line;
	int i = 0;
	signal(SIGQUIT, SIG_IGN);
	while (true)
	{
		signal(SIGINT, handler);
		line = readline("Blackhole_Lover's@Minis(hell):~$ ");
		signal(SIGINT, SIG_IGN);
		if (!line)
			break ;
		if (!*line || ft_videornor(line))
		{
			// free(line);
			continue ;
		}
		add_history(line);
			if (ft_quotesch(line, shell) && ft_pipe(line, shell)
		&& ft_redirections(line, shell))
		{
			ft_cmdhandler(line, shell);
			// display_cmd(shell);
			// if counter dyal l heredoc > 0
			implement_heredoc(shell->cmd);
			ft_execution(shell->cmd);
			ft_freecmdmain(shell);
		}
	}
	ft_malloc(0, 'f');
	printf("exit\n");
	// free(line);
}
