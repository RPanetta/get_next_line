/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:58:33 by rpanetta          #+#    #+#             */
/*   Updated: 2025/11/17 23:43:02 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//Looks for a newline in line
//if there is one: sets charsleft to whatever is "to the right" 
//of the '\n' (the leftover)
//and writes a '\0' at the position of '\n' + 1
//if there isn’t one: returns NULL
char	*ft_separate_line_at_newline(char *line, char **chars_left)
{
	char	*newlineposition;
	char	*result;
	size_t	len;

	newlineposition = ft_find_nl_position(line);
	if (newlineposition)
	{
		len = newlineposition - line + 1;
		result = ft_strndup(line, len);
		if (!result)
			return (NULL);
		if (*(newlineposition + 1) == '\0')
			*chars_left = NULL;
		else
			*chars_left = ft_strdup(newlineposition + 1);
		free(line);
		return (result);
	}
	return (NULL);
}

//Calculates the length of a string, excluding the '\0' byte
//(handles NULL pointers)
size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

//Returns a pointer to the storage space containing the copied string
char	*ft_strdup(const char *s)
{
	char	*copy;
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	copy = malloc(sizeof(char) * (len + 1));
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

//Makes a new copy of a string but only takes a certain number of letters from 
//it—you have a long sentence and you only want to copy the first few words
char	*ft_strndup(const char *s, size_t n)
{
	char	*ptr;
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (len > n)
		len = n;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[len] = '\0';
	return (ptr);
}

//Returns a pointer to the first occurence of \n
//in the string s, or NULL if not found
char	*ft_find_nl_position(const char *s)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}
