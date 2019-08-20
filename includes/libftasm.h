#ifndef LIBFTASM_H
# define LIBFTASM_H

#include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

void    ft_puts(char *str);
int     ft_strlen(char *str);
void    ft_bzero(void *addr, size_t size);
int     ft_isalpha(int c);
int     ft_isdigit(int c);
int     ft_isalnum(int c);
int     ft_isascii(int c);
int     ft_isprint(int c);
int     ft_tolower(int c);
int     ft_toupper(int c);
char    *ft_strcat(char *restrict s1, const char *restrict s2);
void    *ft_memset(void *addr, int c, size_t len);
void    *ft_memcpy(void *restrict dst, const void *restrict src, size_t len);
char    *ft_strdup(char *str);
char    *ft_strndup(char *str, size_t size);
void    ft_cat(int fd);
void    ft_putnbr(int nb);
void    ft_reverse_string(char *str);
void    *ft_memalloc(size_t size);
int     ft_strncmp(const char *s1, const char *s2, size_t s);


#endif