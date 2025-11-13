/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:45:02 by rpanetta          #+#    #+#             */
/*   Updated: 2025/11/13 17:55:51 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free_memory(char **backup, char **buffer)
{
	if (backup && *backup)
	{
		free(*backup);
		*backup = NULL;
	}
	if (buffer && *buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

char	*ft_set_current_line(char *line_buffer)
{
	char	*backup;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
	{
		i++;
	}
	if (line_buffer[i] == '\0' || line_buffer[i + 1] == '\0')
		return (NULL);
	backup = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - (i + 1));
	if (backup[0] == '\0')
	{
		ft_free_memory(&backup, NULL);
		line_buffer[i + 1] = '\0';
		return (NULL);
	}
	line_buffer[i + 1] = '\0';
	return (backup);
}

char	*ft_read_until_newline(int fd, char **backup, char *buffer)
{
	ssize_t	bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (ft_free_memory(backup, NULL), NULL);
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!*backup)
			*backup = ft_strdup("");
		tmp = *backup;
		*backup = ft_strjoin(tmp, buffer);
		ft_free_memory(&tmp, NULL);
		if (!*backup)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (*backup);
}

char	*get_next_line(int fd)
{
	static char	*backup = NULL;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		ft_free_memory(&backup, &buffer);
		return (NULL);
	}
	line = ft_read_until_newline(fd, &backup, buffer);
	free(buffer);
	buffer = NULL;
	if (!line || line[0] == '\0')
	{
		ft_free_memory(&line, &backup);
		return (NULL);
	}
	backup = ft_set_current_line(line);
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