/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:00:53 by abait-ou          #+#    #+#             */
/*   Updated: 2024/09/16 17:10:23 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/Minishell.h"

int main(int ac, char **av, char **env)
{
    t_shell     shell;
    
    (void)ac;
    (void)av;
    shell.envp = ft_environementinit(shell.envp, env);
    shell.envholder = ft_envholder(env, &shell);





    
    // ft_freeenv(shell.envp);
    // ft_freeenvholder(shell.envholder);
    

    return (0);
}