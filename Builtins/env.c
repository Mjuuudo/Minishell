/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:29:37 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/07 21:49:43 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

// void	env_builtin(t_cmd *cmd, t_shell *shell)
// {
//     // case1: no argumentes.
//     if (shell->cmd->args[0] == NULL)
//     {
//         while(shell->envp)
//         {
//             if (shell->envp->value == NULL)
//                 shell->envp = shell->envp->next;
//             else
//                 printf("%s=%s\n", shell->envp->key, shell->envp->value);
//             shell->envp = shell->envp->next;
//         }
//     }
//     // case2: arguments present
//     else
//     {
//         t_envvar *tmp_env;

//         tmp_env = shell->envp;
//         while(tmp_env)
//         {
//             if (ft_strncmp(tmp_env->key, shell->cmd->args[0], ft_strlen(shell->cmd->args[0])) == 0)
//             {
//                 printf("%s=%s\n", tmp_env->key, tmp_env->value);
//                 tmp_env = tmp_env->next;
//             }
//             else
//             {
//                 tmp_env = tmp_env->next;
//             }
//         }

//     }
// }



int	env_builtin(t_cmd *cmd)
{
    t_envvar *current;

    // case1: no arguments - print all environment variables
    if (cmd->args[0] == NULL)
    {
        current = shell.envp;
        while (current)
        {
            if (current->value != NULL)
                printf("%s=%s\n", current->key, current->value);
            current = current->next;
        }
    }
    // case2: with arguments
    else
    {
        current = shell.envp;
        while (current)
        {
            if (ft_strcmp(current->key, cmd->args[0]) == 0)
            {
                if (current->value != NULL)
                    printf("%s=%s\n", current->key, current->value);
                break;
            }
            current = current->next;
        }
    }
	return (0);
}
