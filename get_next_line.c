/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:45:02 by rpanetta          #+#    #+#             */
/*   Updated: 2025/11/16 18:32:26 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//Joins what the string line has (if anything) with what we read in buffer.
//buffer always contains something because we call this function if bytesread > 0
char	*ft_join_line_and_buffer(char *line, char *buffer)
{
	char	*joined;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!line)
		return (ft_strdup(buffer));
	joined = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(buffer) + 1));
	if (!joined)
		return (free(line), NULL);
	while (line[i] != '\0')
	{
		joined[i] = line[i];
		i++;
	}
	while (buffer[j] != '\0')
		joined[i++] = buffer[j++];
	joined[i] = '\0';
	free(line);
	return (joined);
}

//Used when read() return -1 (when it fails)
void	*ft_free_all(char *buffer, char *line, char **chars_left)
{
	free(buffer);
	free(line);
	if (chars_left && *chars_left)
	{
		free(*chars_left);
		*chars_left = NULL;
	}
	return (NULL);
}

char	*ft_read_until_newline(int fd, char *line, char **chars_left)
{
	char	*buffer;
	char	*newline;
	ssize_t	bytesread;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(line), NULL);
	bytesread = read(fd, buffer, BUFFER_SIZE);
	if (bytesread < 0)
		return (ft_free_all(buffer, line, chars_left));
	while (bytesread > 0)
	{
		buffer[bytesread] = '\0';
		line = ft_join_line_and_buffer(line, buffer);
		newline = ft_separate_line_at_newline(line, chars_left);
		if (newline)
		{
			free(buffer);
			return (newline);
		}
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread < 0)
			return (ft_free_all(buffer, line, chars_left));
	}
	return (free(buffer), line);
}

void	ft_extract_line_from_chars_left(char **chars_left, char **line)
{
	char	*new_chars_left;
	char	*new_line_position;
	size_t	len;

	if (!chars_left || !*chars_left)
	{
		*line = NULL;
		return ;
	}
	new_line_position = ft_find_nl_position(*chars_left);
	if (new_line_position)
	{
		len = new_line_position - *chars_left + 1;
		*line = ft_strndup(*chars_left, len);
		new_chars_left = ft_strdup(new_line_position + 1);
		free(*chars_left);
		*chars_left = new_chars_left;
	}
	else
	{
		*line = ft_strdup(*chars_left);
		free(*chars_left);
		*chars_left = NULL;
	}
}

//Static remembers where it stopped in the previous call
char	*get_next_line(int fd)
{
	static char	*chars_left;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (chars_left)
	{
		ft_extract_line_from_chars_left(&chars_left, &line);
		if (ft_find_nl_position(line))
			return (line);
	}
	line = ft_read_until_newline(fd, line, &chars_left);
	if (!line || *line == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	fd = open("text.txt", O_RDONLY);
// 	if (fd < 0)
// 		return (-1);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s", line);
// 		ft_free_memory(&line, NULL);
// 		line = get_next_line(fd);
// 	}
// 	ft_free_memory(&line, NULL);
// 	close(fd);
// 	return (0);
// }