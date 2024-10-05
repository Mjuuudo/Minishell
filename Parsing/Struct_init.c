/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:47:20 by abait-ou          #+#    #+#             */
/*   Updated: 2024/10/05 13:38:38 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

void ft_members_init(t_shell *shell)
{
    shell->cmd = NULL;
    shell->tokens = NULL;
    shell->exit = 0;
}