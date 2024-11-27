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

// static int checkclose(char *arg, int i, char quote)
// {
//     i++;
//     while (arg[i] != '"'  && arg[i])
//         i++;
//     if (arg[i] != quote || !arg[i])
//         return (0);
//     return (1);
// }

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

    // Handle NULL input
    if (!str)
        return (0);

    counter = 0;
    length = 0;
    while (str[counter])
    {
        if (str[counter] == '$')
        {
            counter++;  // Move past $
            
            // Handle $ at end of string
            if (!str[counter])
            {
                length++;  // Count the $ as it's not a variable
                break;
            }
            
            // Check if it's start of valid variable name
            if (ft_isalpha(str[counter]) || str[counter] == '_')
            {
                counter++;  // Skip first char of variable name
                // Skip rest of variable name
                while (str[counter] && (ft_isalnum(str[counter]) || str[counter] == '_'))
                    counter++;
            }
            else
            {
                // $ not followed by valid variable name, count it as regular char
                length++;
                continue;
            }
        }
        else
        {
            length++;
            counter++;
        }
    }
    return (length);
}
static void dupdollarvar(char *str, char *origine)
{
    int counter;
    int dup;

    if (!str || !origine)
        return;

    counter = 0;
    dup = 0;
    while (origine[counter])
    {
        if (origine[counter] == '$')
        {
            counter++;  // Move past the $
            // Handle special case of $ at end of string
            if (!origine[counter])
                break;
            
            // First character must be alpha or underscore
            if (ft_isalpha(origine[counter]) || origine[counter] == '_')
            {
                str[dup++] = origine[counter++];
                // Subsequent characters can be alpha, digit, or underscore
                while (origine[counter] && (ft_isalnum(origine[counter]) || 
                       origine[counter] == '_'))
                {
                    str[dup++] = origine[counter++];
                }
            }
        }
        else
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
    size_t final_size;
    int counter;
    int i;
    int holder;

    // Input validation
    if (!str || !original)
        return (NULL);

    // Calculate required size
    final_size = withoutdollar(original) + ft_strlen(str) + 1;
    final_str = malloc(sizeof(char) * final_size);
    if (!final_str)
        return (NULL);

    counter = 0;
    i = 0;
    holder = 0;

    while (original[counter] && holder < (int)(final_size - 1))
    {
        if (original[counter] == '$')
        {
            counter++;
            // Check for valid variable name start
            if (original[counter] && (ft_isalpha(original[counter]) || 
                original[counter] == '_'))
            {
                // Skip the variable name
                while (original[counter] && (ft_isalnum(original[counter]) || 
                       original[counter] == '_'))
                    counter++;

                // Copy replacement string
                while (str[i] && holder < (int)(final_size - 1))
                    final_str[holder++] = str[i++];
            }
            else
            {
                // Invalid variable name, treat $ as literal
                final_str[holder++] = '$';
            }
        }
        else
        {
            final_str[holder++] = original[counter++];
        }
    }
    final_str[holder] = '\0';
    return (final_str);
}
static int foundornot(char *line, t_envvar *env)
{
    while (env)
    {
        if (!ft_strcmp(line, env->key))
            return (1);
        env = env->next;
    }
    return (0);
    
} 

void ft_vide(t_token *token)
{
    free ((token->cmd));
    token->cmd = malloc(sizeof(char) * 1);
    token->cmd[0] = '\0';
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
    if (!foundornot(dollarvar, env))
    {
        ft_vide(token);
        free(dollarvar);
        return ;
    
    }
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