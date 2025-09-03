/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bavirgil <bavirgil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 23:06:00 by bavirgil          #+#    #+#             */
/*   Updated: 2025/09/03 18:10:50 by bavirgil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# if defined(__APPLE__)
#  define PTRNULL "0x0"
#  define PTRNULL_LEN 3
# elif defined(__linux__)
#  define PTRNULL "(nil)"
#  define PTRNULL_LEN 5
# else
#  define PTRNULL "(nil)"
#  define PTRNULL_LEN 5
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

// Get Next Line Itself
int		find_nl_dup_n(const char *s, size_t n);
int		fill_until_nl(int fd, char **stash);
char	*extract_line_from_stash(char *stash);
char	*update_stash(char *stash);
char	*get_next_line(int fd);

// Utils
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(char const *s);
char	*ft_strdup(char const *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif