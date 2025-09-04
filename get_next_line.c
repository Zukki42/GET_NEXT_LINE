/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bavirgil <bavirgil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:15:59 by bavirgil          #+#    #+#             */
/*   Updated: 2025/09/04 21:34:06 by bavirgil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// extract_line()
// Takes the current buffer (string).
// Finds the first line (up to and including '\n' if present).
// Allocates and returns a new string with just that line.
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

// shift_buffer()
// After a line has been extracted, remove it from the buffer.
// Moves the leftover characters (after '\n') to the front of the buffer.
// Ensures buffer is ready for the next call.
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

// fill_buffer()
// Reads from fd into a temporary string until it finds a '\n' or EOF.
// Keeps appending chunks to `tmp` using ft_strjoin.
// If an error occurs, clears carry and returns NULL.
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
