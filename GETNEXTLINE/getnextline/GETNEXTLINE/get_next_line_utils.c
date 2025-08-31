/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bavirgil <bavirgil@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 23:05:50 by bavirgil          #+#    #+#             */
/*   Updated: 2025/08/31 00:38:24 by bavirgil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Check if either string is NULL and return the other, or NULL if both are NULL
static char	*ft_strjoin_nullcheck(char const *s1, char const *s2)
{
	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	return (NULL);
}

// Allocate memory and concatenate two strings into a new string
static char	*ft_strjoin_copy(char const *s1, char const *s2, size_t len_1,
		size_t len_2)
{
	char	*ptr;
	char	*tmp;

	ptr = malloc(len_1 + len_2 + 1);
	if (!ptr)
		return (NULL);
	tmp = ptr;
	while (*s1)
		*tmp++ = *s1++;
	while (*s2)
		*tmp++ = *s2++;
	*tmp = '\0';
	return (ptr);
}

// Join two strings into a new string, handling NULL cases
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*check;

	check = ft_strjoin_nullcheck(s1, s2);
	if (check)
		return (check);
	return (ft_strjoin_copy(s1, s2, ft_strlen(s1), ft_strlen(s2)));
}

// Calculate the length of a string
size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

// Duplicate a string into a new memory allocation
char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	s2 = (char *)malloc(sizeof(char) * (len + 1));
	if (s2 == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
