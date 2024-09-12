/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:01:38 by abait-ou          #+#    #+#             */
/*   Updated: 2024/09/12 19:14:32 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>


typedef enum s_types
{
    PIPES,
    CMD
}           t_types;

typedef struct s_envvar
{

        char     *value;
        t_envvar *next;
        t_envvar *pev;
        
}              t_envvar;

typedef struct s_token
{
        char    *line;
        t_types  type;
        t_token *next;
        t_token *prev;
        
}               t_token;

typedef struct s_commands
{
        char       *commande;
        char       **table;
        t_commands *next;
        t_commands *prev;
        
}              t_commands;

typedef struct s_shell
{

    
    t_commands  commande;
    t_envvar    envp;
    t_shell     *next;
    t_shell     *prev;
}              t_shell;

// Parsing Functions Prototypes