/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bavirgil <bavirgil@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:15:59 by bavirgil          #+#    #+#             */
/*   Updated: 2025/09/01 17:59:44 by bavirgil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//Find the index of the first '\n' in a string, or return
	//-1 if none is found 
static int	find_nl(const char *s)
{
	int	i;

	if (s == NULL)
		return (-1);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

// Duplicate the first n characters of a string into a new memory allocation
static char	*dup_n(const char *s, size_t n)
{
	char	*out;
	size_t	i;

	out = (char *)malloc(sizeof(char) * (n + 1));
	if (out == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		out[i] = s[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

// Read from the file descriptor until a newline is found or EOF is reached 
static int	fill_until_nl(int fd, char **stash)
{
	char	buf[BUFFER_SIZE + 1];
	int		readn;
	char	*tmp;

	readn = 1;
	while (find_nl(*stash) == -1 && readn > 0)
	{
		readn = read(fd, buf, BUFFER_SIZE);
		if (readn < 0)
			return (-1);
		buf[readn] = '\0';
		tmp = ft_strjoin(*stash, buf);
		if (!tmp)
		{
			free(*stash);
			*stash = NULL;
			return (-1);
		}
		free(*stash);
		*stash = tmp;
	}
	return (readn);
}

// Extract the next line from the stash and update the stash 
static char	*gnl_read_and_extract(char **stash)
{
	int		nl;
	char	*line;
	char	*rest;

	if (!*stash || !(*stash)[0])
		return (NULL);
	nl = find_nl(*stash);
	if (nl >= 0)
	{
		line = dup_n(*stash, nl + 1);
		if (!line)
		{
			free(*stash);
			*stash = NULL;
			return (NULL);
		}
		rest = ft_strdup(*stash + nl + 1);
		if (!rest)
		{
			free(line);
			free(*stash);
			*stash = NULL;
			return (NULL);
		}
	}
	else
	{
		line = dup_n(*stash, ft_strlen(*stash));
		if (!line)
		{
			free(*stash);
			*stash = NULL;
			return (NULL);
		}
		rest = NULL;
	}
	free(*stash);
	*stash = rest;
	return (line);
}

// Main function to read the next line from a file descriptor
char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	int			status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
	{
		stash = ft_strdup("");
		if (!stash)
			return (NULL);
	}
	status = fill_until_nl(fd, &stash);
	if (status == -1 || (status == 0 && !stash[0]))
		return (free(stash), stash = NULL, NULL);
	return (gnl_read_and_extract(&stash));
}
