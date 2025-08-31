/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bavirgil <bavirgil@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 23:06:00 by bavirgil          #+#    #+#             */
/*   Updated: 2025/08/31 00:33:15 by bavirgil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# ifdef __APPLE__
#  define PTRNULL "0x0"
# elif defined(__linux__)
#  define PTRNULL "(nil)"
# else
#  define PTRNULL "(nil)"
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

//Get Next Line Itself
char	*get_next_line(int fd);

// Utils
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(char const *s);
char	*ft_strdup(char const *s1);

#endif