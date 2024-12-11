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
    printf("from duopdollar %s\n", origine);
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
            str[dup++] = origine[counter++];
    }
    str[dup] = '\0';
    printf("from duopdollar %s new str \n", str);
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
            if (original[counter] && (ft_isalnum(original[counter]) || 
                       original[counter] == '_'))
                final_str[holder++] = original[counter++];
        }
    }
    final_str[holder] = '\0';
    return (final_str);
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

void ft_vide(t_token *token)
{
    free ((token->cmd));
    token->cmd = malloc(sizeof(char) * 1);
    token->cmd[0] = '\0';
}
static void noquotes(t_token *token, t_envvar *env)
{
    char *new_string;
    int new_len = ft_strlen(token->cmd) * 100;  // Allocate enough space
    new_string = malloc(sizeof(char) * new_len);
    int j = 0;
    if (!new_string)
        return;

    int i = 0;  // Input string index
    int counter = 0;  // New string index

    while (token->cmd[i])
    {
        if (token->cmd[i] == '$')
        {
            // Extract variable name
            char holder[1024] = {0};
            int a = 0;
            i++;  // Move past $

            // Capture variable name (only alphanumeric or underscore)
            if (ft_isalpha(token->cmd[i]) || token->cmd[i] == '_')
            {
                while (token->cmd[i] && (ft_isalnum(token->cmd[i]) || token->cmd[i] == '_'))
                {
                    holder[a++] = token->cmd[i++];
                }
                holder[a] = '\0';

                // Check if variable exists
                if (a > 0 && !foundornot(holder, env))
                {
                    // No matching environment variable, restore original $
                    // new_string[counter++] = '$';
                    // for (int j = 0; j < a; j++)
                    // {
                    //     new_string[counter++] = holder[j];
                    // }
                    
                    break ;
                }
                else if (a > 0)
                {
                    // Retrieve and copy variable value
                    if (ft_isalnum(holder[0]) || holder[0] == '_')
                    {
                        char *itsvalue = retrivevalue(env, holder);
                        int val_index = 0;
                        while (itsvalue[val_index])
                        {
                            if (counter >= new_len - 1)
                            {
                                // Reallocate if needed
                                new_len *= 2;
                                new_string = realloc(new_string, sizeof(char) * new_len);
                            }
                            new_string[counter++] = itsvalue[val_index++];
                        }
                    
                        free(itsvalue);
                    }
                    else //if (!ft_isalnum(holder[0]) || !(holder[0] == '_'))
                    {
                        new_string[counter++] = holder[j++];
                        j = 0;
                    }
                }
                else
                {
                    // If no valid variable name, keep the $
                    new_string[counter++] = '$';
                }
            }
            else
            {
                // Not a valid variable name, keep the $ and next character
                new_string[counter++] = '$';
                
                // If there's a character after $, add it
                if (token->cmd[i])
                {
                    new_string[counter++] = token->cmd[i++];
                }
            }
        }
        else
        {
            if (counter >= new_len - 1)
            {
                // Reallocate if needed
                new_len *= 2;
                new_string = realloc(new_string, sizeof(char) * new_len);
            }
            new_string[counter++] = token->cmd[i++];
        }
    }
    
    new_string[counter] = '\0';
    
    free(token->cmd);
    token->cmd = new_string;
}

// static void noquotes(t_token *token, t_envvar *env)
// {
//     char *dollarvar;
//     char *itsvalue;
//     char *new_string;
//     char *holder;
//     int counter;
//     int i = 0;
//     int tmp;
//     int a = 0;

   
//     dollarvar = malloc(sizeof(char) * (dollarlength(token->cmd) * 2 + 1));
//     new_string = malloc(sizeof(char) *  (ft_strlen(token->cmd) * 2));
//     if (!dollarvar)
//         return ;
//     while (token->cmd[i])
//     {
//         if (token->cmd[i] == '$')
//         {
//             holder = malloc(sizeof(char) * 1024);
//             i++;
//             if (ft_isalpha(token->cmd[i]) || token->cmd[i] == '_')
//             {
//                 holder[a++] = token->cmd[i++];
//                 // Subsequent characters can be alpha, digit, or underscore
//                 while (token->cmd[i] && (ft_isalnum(token->cmd[i]) || 
//                        token->cmd[i] == '_'))
//                 {
//                     holder[a++] = token->cmd[i++];
//                 }
//                 holder[a] = '\0';
//             }
//             if (!foundornot(holder, env))
//              {
//                 printf("here\n");
//                 ft_vide(token);
//                 free(holder);
//                 return ;
    
//             }
//             itsvalue = malloc(sizeof(char) * (1024 * 2));
//             itsvalue =  retrivevalue(env, holder);
//             printf("from loop %s\n", itsvalue);
//             a = 0;
//             while (itsvalue[a])
//             {
//                 new_string[counter++] = itsvalue[a++];
//             }
//             free(holder);
//             free(itsvalue);
//             tmp = 0;
//         }
//         else
//             new_string[counter++] = token->cmd[i++];
//     }
    
//     // dupdollarvar(dollarvar, token->cmd);
//     // if (!foundornot(dollarvar, env))
//     // {
//     //     printf("here\n");
//     //     ft_vide(token);
//     //     free(dollarvar);
//     //     return ;
    
//     // }
//     // itsvalue = retrivevalue(env, dollarvar);
//     // if (!itsvalue)
//     //     exit(1) ;
//     // new_string = finalstring(itsvalue, token->cmd);
//     free(token->cmd);
//     // free(dollarvar);
//     // free(itsvalue);
//     token->cmd = new_string;
// }
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