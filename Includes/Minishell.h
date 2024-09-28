/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:01:38 by abait-ou          #+#    #+#             */
/*   Updated: 2024/09/28 18:50:11 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

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
        char    *cmd;
        t_types  type;
        t_token *next;
        t_token *prev;    
};

struct s_commands
{
        char       *commande;
        char       **table;     
};

struct s_shell
{
    int         shell_level;
    int         exit;
    char        **envholder;
    t_commands  commande;
    t_envvar    *envp;
    t_shell     *next;
    t_shell     *prev;
};

// Parsing Environement Variables Functions Prototypes

void      ft_addnodeenv(t_envvar **list, char *value);
t_envvar *ft_returnlastnodeenv(t_envvar *list);
void      ft_initnodeenv(t_envvar *node, char *value);
t_envvar  *ft_environementinit(t_envvar *envliste, char **env);
char     **ft_envholder(char **env, t_shell *shell);

// Parsing The STDIN Function Prototypes
        // Lexcer Section
void    ft_members_init(t_shell *shell);
void    ft_shell_on(t_shell *shell);
void    ft_lexcer(char *commande, t_shell *shell);
void    ft_formatcorrection(t_shell *shell, char *line);
int     ft_spacecalculation(char *line);
int     ft_quotes(char *line, int index);

// Error And Memory Management Functions

void ft_freeenv(t_envvar    *list);
void ft_freeenvholder(char **envholder);
void ft_freecmd(char *line, char **table);


// Tools Function Prototypes

char	*ft_strdup(const char *str);
size_t	ft_strlen(const char *str);
char    *ft_strncpy(char *src, char *dst, unsigned int len);
int	ft_isalpha(int c);
void	*ft_calloc(size_t nmemb, size_t size);
int	ft_ispace(char c);
// char	**ft_split(char  *s, char c);
char **ft_split(char *line, char sep);