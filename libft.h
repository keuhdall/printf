/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 18:29:58 by lmarques          #+#    #+#             */
/*   Updated: 2017/09/03 06:33:21 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>

size_t				ft_strlen(const char *str);
int					ft_strchr_index(char *s, int c);
int					ft_atoi_addr(char **s);
void				ft_bzero(void *s, size_t n);
void				*ft_memchr(const void *mem, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
double				ft_pow(double n, int pow);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_wcharsize(unsigned c);
size_t				ft_wstrlen(unsigned *s);
char				*ft_strdup(const char *s1);

#endif
