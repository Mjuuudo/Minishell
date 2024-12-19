/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oer-refa <oer-refa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:34:37 by oer-refa          #+#    #+#             */
/*   Updated: 2024/12/11 09:49:31 by oer-refa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] != '\0' && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len1;
	size_t	len2;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	len1 = 0;
	len2 = 0;
	len1 = strlen(s1);
	len2 = strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	i += ft_strlcpy(ptr + i, s1, len1 + 1);
	i += ft_strlcpy(ptr + i, s2, len2 + 1);
	ptr[len1 + len2] = '\0';
	return (ptr);
}

int	ft_len(int value)
{
	int	len;

	len = 0;
	if (value < 0)
	{
		value *= -1;
		len++;
	}
	if (value == 0)
		return (1);
	while (value)
	{
		value = value / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		sign;

	sign = 0;
	len = ft_len(n);
	if (n == -2147483648)
		return (strdup("-2147483648"));
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
		sign = 1;
	}
	str[len] = '\0';
	len--;
	while (sign <= len)
	{
		str[len--] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
