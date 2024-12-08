/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:00:53 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/07 20:52:18 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/Minishell.h"

t_shell	shell;

int	main(int ac, char **av, char **env)
{

	(void)ac;
	(void)av;
	shell.envp = NULL;
	shell.envp = ft_environementinit(shell.envp, env);
	shell.envholder = ft_envholder(env, &shell);
	ft_members_init(&shell);
	ft_shell_on(&shell);
	ft_freeenv(shell.envp);
	ft_freeenvholder(shell.envholder);
	return (0);
}
