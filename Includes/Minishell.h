/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:01:38 by abait-ou          #+#    #+#             */
/*   Updated: 2024/09/16 17:08:07 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

typedef struct s_envvar t_envvar;
typedef struct s_token  t_token;
typedef struct s_commands t_commands;
typedef struct s_shell  t_shell;


typedef enum s_types
{
    PIPES,
    CMD,
    FLAG
}           t_types;

struct s_envvar
{
        char     *key;
        char     *value;  
        t_envvar *next;
        t_envvar *prev;
        
};

struct s_token
{
        char    *line;
        t_types  type;
        t_token *next;
        t_token *prev;
        
};

struct s_commands
{
        char       *commande;
        char       **table;
        t_commands *next;
        t_commands *prev;
        
};

struct s_shell
{
    int         exit;
    char        **envholder;
    char        **cmd_history;
    t_commands  *commande;
    t_envvar    *envp;
    t_shell     *next;
    t_shell     *prev;
};

// Parsing Environement Variables Functions Prototypes

char *ft_strncpy(char *src, char *dst, unsigned int len);

void      ft_addnodeenv(t_envvar **list, char *value);
t_envvar *ft_returnlastnodeenv(t_envvar *list);
void      ft_initnodeenv(t_envvar *node, char *value);
t_envvar  *ft_environementinit(t_envvar *envliste, char **env);
char     **ft_envholder(char **env, t_shell *shell);

// Error And Memory Management Functions

void ft_freeenv(t_envvar    *list);
void ft_freeenvholder(char **envholder);


// Tools Function Prototypes

char	*ft_strdup(const char *str);
size_t	ft_strlen(const char *str);