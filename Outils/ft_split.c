/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ou <abait-ou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:30:08 by abait-ou          #+#    #+#             */
/*   Updated: 2024/12/18 15:29:35 by abait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

static int	check_quote(char *str, int a)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			j = i + 1;
			while (str[j] && str[j] != str[i])
				j++;
			if (j == (int)ft_strlen(str))
				return (0);
			if (a > i && a < j)
				return (1);
			i = j + 1;
		}
		else
			i++;
	}
	return (0);
}

static int	count_words(char *str, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && ft_strchr(str[i], charset) && !check_quote(str, i))
			i++;
		if (str[i])
			count++;
		while (str[i] && (!ft_strchr(str[i], charset) || (ft_strchr(str[i],
						charset) && check_quote(str, i))))
			i++;
	}
	return (count);
}

static int	char_sep(char *str, char *charset)
{
	int	i;

	i = 0;
	while (str[i] && (!ft_strchr(str[i], charset) || (ft_strchr(str[i], charset)
				&& check_quote(str, i))))
		i++;
	return (i);
}

static char	*ft_words(char *str, char *charset)
{
	int		len;
	int		i;
	char	*word;

	len = char_sep(str, charset);
	i = 0;
	word = (char *)malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		word[i] = str[i];
		if (!str[i])
			return (NULL);
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *str, char *charset)
{
	char	**strings;
	int		i;
	int		j;
	int		str_len;

	i = 0;
	j = 0;
	str_len = count_words(str, charset);
	strings = (char **)malloc(sizeof(char *) * (str_len + 1));
	while (str[j])
	{
		while (str[j] && ft_strchr(str[j], charset) && !check_quote(str, j))
			j++;
		if (str[j])
		{
			strings[i] = ft_words(&str[j], charset);
			i++;
		}
		while (str[j] && (!ft_strchr(str[j], charset) || (ft_strchr(str[j],
						charset) && check_quote(str, j))))
			j++;
	}
	strings[i] = NULL;
	return (strings);
}
