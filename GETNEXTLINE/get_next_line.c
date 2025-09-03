/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bavirgil <bavirgil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:15:59 by bavirgil          #+#    #+#             */
/*   Updated: 2025/09/03 20:01:29 by bavirgil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Find the index of the first '\n' in a string, or return -1 if none is found
int	find_nl_dup_n(const char *s, size_t n)
{
	size_t	i;

	if (!s)
		return (-1);
	i = 0;
	while (i < n && s[i])
	{
		if (s[i] == '\n')
			return ((int)i);
		i++;
	}
	return (-1);
}

// Read from the file descriptor until a newline is found or EOF is reached
int	fill_until_nl(int fd, char **stash)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;
	int		nl_index;
	char	*tmp;

	{
		nl_index = -1;
		while (nl_index == -1)
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read <= 0)
				break ;
			buffer[bytes_read] = '\0';
			if (!*stash)
				*stash = ft_strdup(buffer);
			else
			{
				tmp = ft_strjoin(*stash, buffer);
				free(*stash);
				*stash = tmp;
			}
			nl_index = find_nl_dup_n(*stash, ft_strlen(*stash));
		}
		return (bytes_read);
	}
}

// Extract the next line from the stash
char	*extract_line_from_stash(char *stash)
{
	int		i;
	char	*line;

	if (!stash || !*stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = ft_substr(stash, 0, i);
	return (line);
}

// Update the stash after extracting a line
char	*update_stash(char *stash)
{
	int		i;
	char	*new_stash;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_substr(stash, i + 1, ft_strlen(stash) - (i + 1));
	free(stash);
	return (new_stash);
}

// Main function to read the next line from a file descriptor
char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = fill_until_nl(fd, &stash);
	if (!stash || bytes_read < 0)
		return (NULL);
	line = extract_line_from_stash(stash);
	stash = update_stash(stash);
	return (line);
}
