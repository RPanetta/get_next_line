/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:58:33 by rpanetta          #+#    #+#             */
/*   Updated: 2025/11/10 13:48:09 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*copy;
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	copy = malloc(len + 1);
	if (copy == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*result;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(sizeof(char) * (len1 + len2 + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		result[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		result[i] = s2[i - len1];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			return ((char *)(s + i));
		}
		i++;
	}
	if ((char)c == '\0')
	{
		return ((char *)(s + i));
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	real_len;
	char	*substr;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
	{
		substr = malloc(1);
		if (substr == NULL)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	real_len = ft_strlen(s) - start;
	if (real_len > len)
		real_len = len;
	substr = malloc(real_len + 1);
	if (substr == NULL)
		return (NULL);
	i = -1;
	while (++i < real_len)
		substr[i] = s[start + i];
	substr[real_len] = '\0';
	return (substr);
}
