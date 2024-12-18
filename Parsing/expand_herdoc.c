/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:41:53 by marvin            #+#    #+#             */
/*   Updated: 2024/12/12 13:19:56 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

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
    if (!value)
    {
        printf("Expande Failed : Variable Not Founed\n");
        exit(1);
    }
    return (value);
}
static int foundornot(char *line, t_envvar *env)
{
   
    if (!line || !env)
        return (0);
    while (env)
    {
        if (!env->key)
            continue;  
        if (ft_strcmp(line, env->key) == 0)
            return (1);
        env = env->next;
    }
    return (0);
}                        

static char *noquotes(char *line, t_envvar *env,int i, int j, int counter)
{
    char *new_string;
    int a;
    char holder[1024];
    char *itsvalue;
    int val_index;


    new_string = malloc(sizeof(char) * (ft_strlen(line) * 100 * 5));
    if (!new_string)
        return NULL;
    while (line[i])
    {
        if (line[i] == '$')
        {
            a = 0;
            i++;  
            if (ft_isalpha(line[i]) || line[i] == '_')
            {
                while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
                    holder[a++] = line[i++];
                holder[a] = '\0';
                if (a > 0 && !foundornot(holder, env))
                    break ;
                else if (a > 0)
                {
                    if (ft_isalnum(holder[0]) || holder[0] == '_')
                    {
                        itsvalue = retrivevalue(env, holder);
                        val_index = 0;
                        while (itsvalue[val_index])
                            new_string[counter++] = itsvalue[val_index++];
                        free(itsvalue);
                    }
                    else 
                    {
                        new_string[counter++] = holder[j++];
                        j = 0;
                    }
                }
                else
                    new_string[counter++] = '$';
            }
            else
            {
                new_string[counter++] = '$';
                if (line[i])
                    new_string[counter++] = line[i++];
            }
        }
        else
            new_string[counter++] = line[i++];
    }
    new_string[counter] = '\0';
    free(line);
    line = new_string;
    return (line);
}

static char  *ft_replace(char *line, t_envvar *env)
{
    return(noquotes(line, env, 0, 0, 0));
}   

char *ft_expandherdoc(char *line, t_envvar *env)
{
    char *new_line;
    
    if (ft_checkdollar(line))
    {
        line = ft_replace(line, env);
    }
    return (line);
}