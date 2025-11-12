/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:45:02 by rpanetta          #+#    #+#             */
/*   Updated: 2025/11/12 18:17:25 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_set_current_line(char *line_buffer)
{
	char	*backup;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
	{
		i++;
	}
	if (line_buffer[i] == 0 || line_buffer[i + 1] == 0)
		return (NULL);
	backup = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*backup == 0)
	{
		free(backup);
		backup = NULL;
	}
	line_buffer[i + 1] = 0;
	return (backup);
}

static char	*ft_read_until_newline(int fd, char **backup, char *buffer)
{
	ssize_t	bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(*backup);
			*backup = NULL;
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!*backup)
			*backup = ft_strdup("");
		tmp = *backup;
		*backup = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (!*backup)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (*backup);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE < 0)
	{
		free(backup);
		free(buffer);
		backup = NULL;
		buffer = NULL;
		return (NULL);
	}
	line = ft_read_until_newline(fd, &backup, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	backup = ft_set_current_line(line);
	return (line);
}

// int	main(void)
// {
// 	int		fd;

// 	fd = open("text.txt", O_RDWR);
// 	printf("%s\n", get_next_line(fd));
// 	printf("%s\n", get_next_line(fd));
// 	printf("%s\n", get_next_line(fd));
// 	printf("%s\n", get_next_line(fd));
// 	printf("%s\n", get_next_line(fd));
// 	printf("%s\n", get_next_line(fd));
// 	printf("%s\n", get_next_line(fd));
// 	printf("%s\n", get_next_line(fd));
// 	return (0);
// }