/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bavirgil <bavirgil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:15:59 by bavirgil          #+#    #+#             */
/*   Updated: 2025/10/15 19:32:56 by bavirgil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// extract_line — extracts a single line from the buffer :D
// Takes the current buffer (string) and copies characters until '\n' or '\0'.
// Returns a newly malloc’d string containing one full line.
// If no data is left, returns NULL.
static char	*extract_line(char *buf)
{
	size_t	k;
	size_t	len;
	char	*res;

	if (!buf || !*buf)
		return (NULL);
	len = 0;
	while (buf[len] && buf[len] != '\n')
		len++;
	if (buf[len] == '\n')
		len++;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	k = 0;
	while (k < len)
	{
		res[k] = buf[k];
		k++;
	}
	res[k] = '\0';
	return (res);
}

// shift_buffer — moves leftover text to the front of the buffer :D
// After a line is read, removes it from `buf` and keeps what’s after '\n'.
// Prepares the buffer for the next call to get_next_line().
static void	shift_buffer(char *buf)
{
	size_t	start;
	size_t	pos;

	start = 0;
	while (buf[start] && buf[start] != '\n')
		start++;
	if (buf[start] == '\n')
		start++;
	pos = 0;
	while (buf[start])
		buf[pos++] = buf[start++];
	buf[pos] = '\0';
}

// fill_buffer — reads from fd into tmp until '\n' or EOF :D
// Uses ft_strjoin() to keep appending chunks until a full line is found.
// If a read error occurs, resets the carry buffer and returns NULL.
static char	*fill_buffer(int fd, char *tmp, char *carry)
{
	char	read_chunk[BUFFER_SIZE + 1];
	int		n;
	char	*old;

	n = 1;
	while (n > 0 && !ft_strchr(tmp, '\n'))
	{
		n = read(fd, read_chunk, BUFFER_SIZE);
		if (n < 0)
			return (free(tmp), carry[0] = '\0', NULL);
		if (n == 0)
			break ;
		read_chunk[n] = '\0';
		old = tmp;
		tmp = ft_strjoin(old, read_chunk);
		free(old);
		if (!tmp)
			return (NULL);
	}
	return (tmp);
}

// get_next_line — reads one line at a time from a file descriptor :D
// Uses a static carry buffer to store leftovers between calls.
// Returns a malloc’d string containing the next line, or NULL on EOF/error.
char	*get_next_line(int fd)
{
	static char	carry[BUFFER_SIZE + 1];
	char		*tmp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (carry[0] = '\0', NULL);
	if (ft_strchr(carry, '\n'))
	{
		line = extract_line(carry);
		shift_buffer(carry);
		return (line);
	}
	tmp = ft_strdup(carry);
	if (!tmp)
		return (NULL);
	carry[0] = '\0';
	tmp = fill_buffer(fd, tmp, carry);
	if (!tmp)
		return (NULL);
	line = extract_line(tmp);
	if (line && tmp[0])
		ft_strlcpy(carry, tmp + ft_strlen(line), BUFFER_SIZE + 1);
	free(tmp);
	return (line);
}

// Example usage :D
// Compile with your helper files (libft or your string utils).
// #include <fcntl.h>
// #include <stdio.h>
//
// int	main(void)
// {
// 	int		fd;
// 	char	*next_line;
// 	int		i;
//
// 	i = 0;
// 	fd = open("a.out", O_RDONLY);
// 	while (i++ < 140)
// 	{
// 		next_line = get_next_line(fd);
// 		printf("Line: %s", next_line);
// 		free(next_line);
// 	}
// 	close(fd);
// 	return (0);
// }
