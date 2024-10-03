/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:01:38 by abait-ou          #+#    #+#             */
/*   Updated: 2024/10/03 18:58:20 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
#define MINISHELL_H

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
typedef struct s_cmd    t_cmd;
typedef struct s_redirection t_redirection;

typedef enum s_types
{
    PIPE,
    STR,
    GREAT,
    DGREAT,
    LESS,
    LLESS
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

struct s_cmd
{
        char    *order;
        char    **args;
        t_token *next;
        t_token *prev;    
};

struct s_commands
{
        char       *commande;
        char       **table;     
};

struct s_redirection
{
	t_types		identifer;
	char		*file;
	t_redirection	*next;
        t_redirection	*prev;
};

struct s_shell
{
    int         shell_level;
    int         exit;
    char        **envholder;
    
    t_commands  commande;
    t_token     *tokens;
    t_token     *actual;
    t_cmd       *cmd;
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
int     ft_quotes(char *line, int index);
void  ft_cmdhandler(char *line, t_shell *shell);
int  count_spaces(char *line);
char *spaced_string(char *line, t_shell *shell, int spaces, int counter_2);
void ft_cmdliste(t_shell *shell);
t_token *ft_returnlastnodecmd(t_token *list);

        // Parser Section
        
void ft_parser(t_shell *shell);


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
void    ft_redirections(char *line, t_shell *shell);
void    ft_pipe(char *line, t_shell *shell);
void    ft_quotesch(char *line, t_shell *shell);
int	ft_strchr(int c, const char *s);
char	**ft_split(char *str, char *charset);
int	ft_strncmp(const char *s1, const char *s2, size_t n);



// Seconde
void ft_spacedstring(char *line, int spaces, char *dest, int counter_2);

t_cmd *ft_returnlastnodecmd2(t_cmd *list);
void ft_cmdliste_2(t_shell *shell, t_token *token);
void ft_addnodecmd(t_shell *shell);

#endif

