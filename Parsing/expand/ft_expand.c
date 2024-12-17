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
    return (value);
}

static int foundornot(char *line, t_envvar *env)
{
    // Check for NULL inputs first
    if (!line || !env)
        return (0);

    
    while (env)
    {
        // Additional safety checks
        if (!env->key)
            continue;  // Skip entries with NULL keys

        if (ft_strcmp(line, env->key) == 0)
            return (1);
        
        env = env->next;
    }
    return (0);
}     
\
static int is_valid_var_start(char c)
{
    return (ft_isalpha(c) || c == '_');
}

static int is_alnum_or_underscore(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (!(ft_isalnum(str[i]) || str[i] == '_'))
            return 0;
        i++;
    }
    return 1;
}

static int extract_var_name(char *input, char *holder, int *index)
{
    int a = 0;
    while (input[*index] && (ft_isalnum(input[*index]) || input[*index] == '_'))
    {
        holder[a++] = input[(*index)++];
    }
    holder[a] = '\0';
    return a;
}

static int handle_env_var(char *new_string, char *holder, t_envvar *env, 
                          int *counter)
{
    char *itsvalue;
    int val_index;

    itsvalue = retrivevalue(env, holder);
    val_index = 0;
    if (!foundornot(holder, env))
    {
        if (is_alnum_or_underscore(holder))
            return (1);
        return (0);
    }
    
    while (itsvalue[val_index])
        new_string[(*counter)++] = itsvalue[val_index++];
    free(itsvalue);
    return 1;
}

static int handle_dollar_sign(char *input, char *new_string, t_envvar *env, 
                               int *i, int *counter)
{
    char holder[1024] = {0};
    int var_len;
    int j = 0;
    
    (*i)++; 
    if (!is_valid_var_start(input[*i]))
    {
        new_string[(*counter)++] = '$';
        if (input[*i])
            new_string[(*counter)++] = input[(*i)++];
        return 1;
    }
    var_len =  extract_var_name(input, holder, i);
    if (var_len == 0)
    {
        new_string[(*counter)++] = '$';
        return 1;
    }
    if (!handle_env_var(new_string, holder, env, counter))
    {
        new_string[(*counter)++] = '$';
        while (j < var_len)
            new_string[(*counter)++] = holder[j++];
    }
    return (1);
}

static void noquotes(t_token *token, t_envvar *env)
{
    int new_len;
    char *new_string;
    int i;
    int counter;
    
    (i = 0, counter = 0);
    new_len = ft_strlen(token->cmd) * 100;
    new_string = malloc(sizeof(char) * new_len);
    if (!new_string)
        return;
    while (token->cmd[i])
    {
        if (token->cmd[i] == '$')
        {
            if (!handle_dollar_sign(token->cmd, new_string, env, &i, &counter))
                break;
        }
        else
            new_string[counter++] = token->cmd[i++];
    }
    new_string[counter] = '\0';
    free(token->cmd);
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

int wordcount(char *str)
{
    int counter;
    int words;

    counter = 0;
    words = 0;
    while (isspace(str[counter]))
        counter++;
    if (str[counter] != '\0')
        words++;
    while (str[counter])
    {
        if (isspace(str[counter]))
        {
            while (isspace(str[counter]))
                counter++;
            if (str[counter] != '\0')
                words++;
        }
        counter++;
    }
    return (words);
}

int ft_expand(t_token *token, t_envvar *env)
{
    if (ft_checkdollar(token->cmd))
    {
        ft_replace(token, env);
    }
    return (wordcount(token->cmd));
}