/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expnad.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:41:53 by marvin            #+#    #+#             */
/*   Updated: 2024/10/11 13:41:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Minishell.h"

static int checkclose(char *arg, int i, char quote)
{
    i++;
    while (arg[i] != '"'  && arg[i])
        i++;
    if (arg[i] != quote || !arg[i])
        return (0);
    return (1);
}

static int isinornot(const char *arg) {
    int i = 0;
    int in_quote = 0; // 0: outside quotes, 1: inside single quotes, 2: inside double quotes
    int single_quote_count = 0;
    int double_quote_count = 0;

    while (arg[i]) {
        if (arg[i] == '"' && in_quote != 1) {
            in_quote = (in_quote == 2) ? 0 : 2; // Toggle double quotes
            double_quote_count++;
        } else if (arg[i] == '\'' && in_quote != 2) {
            in_quote = (in_quote == 1) ? 0 : 1; // Toggle single quotes
            single_quote_count++;
        }
        i++;
    }
    if (single_quote_count > double_quote_count) {
        return 1; // Single quotes are the main quote type
    } else if (double_quote_count > single_quote_count) {
        return 2; // Double quotes are the main quote type
    } else {
        return 0; // No clear main quote type or equal usage
    }
}

static int ft_checkdollar(char *arg)
{
    int counter;

    counter = 0;
    while (arg[counter])
    {
        if (arg[counter] == '$')
        {
            return (1);
        }
        counter++;
    }
    return (0);
}

static int dollarlength(char *str)
{
    int counter;
    int length;

    counter = 0;
    length = 0;
    while (str[counter])
    {
        if (str[counter] == '$')
        {
            counter++;
            while (ft_isalpha(str[counter]))
                (counter++, length++);
            return (length);
        }
        counter++;
    }
    return (length);
}

static int withoutdollar(char *str)
{
    int counter;
    int length;

    counter = 0;
    length = 0;
    while (str[counter])
    {
        if (str[counter] == '$')
        {
            counter++;
            while (str[counter])
                counter++;
        }
        counter++;
        length++;
    }
    return (length);
}
static void dupdollarvar(char *str, char *origine)
{
    int counter;
    int dup;

    counter = 0;
    dup = 0;
    while (origine[counter])
    {
        if (origine[counter] == '$')
        {
            counter++;
            while (ft_isalpha(origine[counter]) || origine[counter])
            {
                str[dup] = origine[counter];
                (dup++, counter++);
            }
        }
        counter++;
    }
    str[dup] = '\0';
}

static char *retrivevalue(t_envvar *env,  char *key)
{
    char *value;

    while (env)
    {
        if (!ft_strncmp(env->key, key, ft_strlen(key)))
        {
                value = ft_strdup(env->value);
                break ;
        }
        env = env->next;
    }
    if (!value)
    {
        printf("Expande Failed : Variable Not Founed\n");
        exit(1);
    }
    return (value);
}

static char *finalstring(char *str, char *original)
{
    char *final_str;
    int counter;
    int i;
    int holder;

    final_str = malloc(sizeof(char) * (withoutdollar(original) + ft_strlen(str) + 1));
    if (!final_str)
        return NULL;
    counter = 0;
     i = 0;
    holder = 0;
    while (original[counter])
    {
        if (original[counter] == '$')
        {
            counter++;
            while (ft_isalpha(original[counter]))
                    counter++;
            while (str[i])
            {
                final_str[holder] = str[i];
                holder++;
                 i++;
                continue ;
            }
        }
            final_str[holder] = original[counter];
            holder++;
             counter++;
    }
    final_str[holder] = '\0';
     return (final_str);
}



static void noquotes(t_token *token, t_envvar *env)
{
    char *dollarvar;
    char *itsvalue;
    char *new_string;

   
    dollarvar = malloc(sizeof(char) * (dollarlength(token->cmd) + 1));
    if (!dollarvar)
        return ;
    dupdollarvar(dollarvar, token->cmd);
    itsvalue = retrivevalue(env, dollarvar);
    if (!itsvalue)
        exit(1) ;
    new_string = finalstring(itsvalue, token->cmd);
    free(token->cmd);
    free(dollarvar);
    free(itsvalue);
    token->cmd = new_string;
}
static int indexdol(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] == '$')
            return (i);
        i++;
    }
    return 0;
}

static void ft_replace(t_token *token, t_envvar *env)
{
    
    if (ft_quotes(token->cmd, indexdol(token->cmd)))
    {
        if (isinornot(token->cmd) == 2)
        {
            noquotes(token, env);
        }
        else 
            return ;
    }
    else
        noquotes(token, env);
}

void ft_expand(t_token *token, t_envvar *env)
{
    if (ft_checkdollar(token->cmd))
    {
        ft_replace(token, env);
    }
}