/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bavirgil <bavirgil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 23:06:00 by bavirgil          #+#    #+#             */
/*   Updated: 2025/10/15 19:33:36 by bavirgil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

/* ************************************************************************** */
/*                             PLATFORM SETTINGS                              */
/* ************************************************************************** */

/*
** Pointer display settings (mainly used for debugging consistency)
** - macOS  → "0x0"
** - Linux  → "(nil)"
** Defaults to Linux format if unknown.
*/
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

/* ************************************************************************** */
/*                                 CONSTANTS                                  */
/* ************************************************************************** */

/*
** BUFFER_SIZE defines how many bytes are read at once.
** You can change this when compiling:
**   gcc -D BUFFER_SIZE=42 get_next_line.c ...
*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

/* ************************************************************************** */
/*                              FUNCTION PROTOTYPES                           */
/* ************************************************************************** */

/*
** String helper functions — similar to Libft ones
*/
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);

/*
** Core function
** Reads one line at a time from the given file descriptor.
** Returns a malloc'd string containing the next line, or NULL on EOF/error.
*/
char	*get_next_line(int fd);

#endif
