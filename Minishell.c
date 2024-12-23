/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:00:53 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/23 00:42:24 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// g_shell	shell;

#include "Includes/Minishell.h"

g_shell	shell;

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	shell.envp = NULL;
	shell.envp = ft_environementinit(shell.envp, env);
	shell.envholder = ft_envholder(env, &shell);
	ft_members_init(&shell);
	fg_shell_on(&shell);
	return (0);
}
