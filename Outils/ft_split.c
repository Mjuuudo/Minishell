/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:30:08 by abait-ou          #+#    #+#             */
/*   Updated: 2024/09/28 18:29:34 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

static int count_elements(char *line, char sep)
{
    int counter = 0;
    int word = 0;

    
    while (ft_ispace(line[counter]))
        counter++;
    if (line[counter] == '\0')
        return (0);
    while (line[counter])
    {
        if (line[counter] == sep && !ft_quotes(line, counter))
        {    word++;
            while (line[counter] == sep)
                counter++;
        }
        counter++;
    }
    return (word + 1);
}

static char	*ft_strndup(const char *s, size_t n)
{
	char	*result;
	size_t	i;

	if (!s)
		return (NULL);
	result = (char *)malloc(n + 1);
	if (!result)
		return (NULL);
	i = 0;
	if (result)
	{
		while (i < n)
		{
			result[i] = s[i];
			i++;
		}
		result[n] = '\0';
	}
	return (result);
}

char **ft_split(char *line, char sep) {
    char **holder;
    int length = count_elements(line, sep);
    char *start;
    int counter = 0;
    int i;

    holder = (char **)malloc(sizeof(char *) * (length + 2));
    if (!holder)
        return NULL;
    length = 0; 
    while (line[counter] && length < count_elements(line, sep))
    {
        if (ft_quotes(line, counter))
        {
            start = line + counter;
            i = counter;
            while (ft_quotes(line, counter))
                counter++;
            holder[length++] = ft_strndup(start, (counter - i));
            counter++;
        }
        else if (!ft_ispace(line[counter]))
        {
            start = line + counter;
            i = counter;
            while (!ft_ispace(line[counter]))
                counter++;
            holder[length++] = ft_strndup(start, (counter - i));
            counter++;
        }
        else
            counter++;
    }
    holder[length] = NULL; 
    return holder;
}