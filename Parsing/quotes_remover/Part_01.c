#include "../../Includes/Minishell.h"

static int quote_or_not(char *line)
{
    int counter;

    counter = 0;
    while (line[counter])
    {
        if (line[counter] == '"' || line[counter] == 39)
            return (1);
        counter++;
    }
    return (0);
}


static char *removequotes(char *line)
{
    int counter;
    char *new_str;
    int  i;
    char sym;
    int flag;

    new_str = malloc(sizeof(char) * (ft_strlen(line) * 2 + 1));
    if (!new_str)
        return (NULL);
    counter = 0;
    flag = 0;
    i = 0;
    while (line[counter])
    {
        if ((line[counter] == '"' || line[counter] == 39) && flag == 0)
        {
            flag = 1;
            sym = line[counter];
            counter++;
        }
        else if (sym == line[counter] && flag == 1)
        {
            flag = 0;
            sym = 0;
            counter++;
        }
        else
        {
            new_str[i] = line[counter];
            i++;
            counter++;
        } 
    }
    new_str[i] = 0;
    return (new_str);
}


void ft_quotesremove(t_cmd **node)
{
    int counter;
    char *new;

    counter = 0;
    if (quote_or_not((*node)->order))
    {
            printf("here\n");
            new = removequotes((*node)->order);
            free((*node)->order);
            (*node)->order = ft_strdup(new);
            free(new);
    }
    while ((*node)->args[counter])
    {
        if (quote_or_not((*node)->args[counter]))
        {
            new = removequotes((*node)->args[counter]);
            free((*node)->args[counter]);
            (*node)->args[counter] = ft_strdup(new);
            free(new);
        }
        counter++;
    }
}