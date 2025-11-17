/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:51:39 by rpanetta          #+#    #+#             */
/*   Updated: 2025/11/17 12:52:04 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
void	ft_extract_line_from_chars_left(char **chars_left, char **line);
char	*ft_find_nl_position(const char *s);
char	*ft_read_until_newline(int fd, char *line, char **chars_left);
size_t	ft_strlen(const char *str);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strdup(const char *s);
char	*ft_join_line_and_buffer(char *line, char *buffer);
char	*ft_separate_line_at_newline(char *line, char **chars_left);
void	*ft_free_all(char *buffer, char *line, char **chars_left);

#endif