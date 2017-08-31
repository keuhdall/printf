/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 18:37:46 by lmarques          #+#    #+#             */
/*   Updated: 2017/08/31 20:37:02 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** --------------------------- Librairies --------------------------------------
*/

# include "libft.h"
# include <stdarg.h>
# include <errno.h>
# define PF_BUF_SIZE	64
# define MAX(a, b)		b & ((a - b) >> 31) | a & (~(a - b) >> 31)
# define MIN(a, b)		a & ((a - b) >> 31) | b & (~(a - b) >> 31)

/*
** --------------------------- Masks Definition --------------------------------
*/

# define FL_SHARP		(1 << 0)
# define FL_SPACE		(1 << 1)
# define FL_PLUS 		(1 << 2)
# define FL_MINUS		(1 << 3)
# define FL_ZERO		(1 << 4)
# define FL_WILDCARD	(1 << 5)
# define FL_UPCASE		(1 << 6)
# define FL_SHORT		(1 << 7)
# define FL_SHORT2		(1 << 8)
# define FL_LONG		(1 << 9)
# define FL_LONG2		(1 << 10)
# define FL_INTMAX		(1 << 11)
# define FL_SIZE_T		(1 << 12)
# define FL_MIN_LEN		(1 << 13)
# define FL_APP_ACCU	(1 << 14)
# define FL_POINTER		(1 << 15)

/*
** --------------------------- ft_printf variables -----------------------------
** A) Printf writes the output and then returns the len (int)
** B) f stands for flag, defined above and extensively described in parsing.c
** C) min_len (digit after %) and accu (. after %) ~ parsing.c
** D) padding is the resulting from C and the output length.
** E) printed is the temporary len of chars to be send to the buffer
** F) fd is the file descriptor. 1 for ft_printf and can be any with ft_dprintf
** G) buffer_index and buff are related to the buffer function ~ buffer.c
** H) the variadic list (va_list ap) and the format are stored in the structure
** I) c is a temp char (as unsigned int) in order to have a single declaration
*/

typedef struct	s_printf
{
	int			len;
	short		f;
	int			min_len;
	int			accu;
	int			padding;
	int			printed;
	int			fd;
	size_t		buff_index;
	char		buff[PF_BUF_SIZE];
	va_list		lst;
	char		*format;
	unsigned	c;
	int			i;
	int			n;
}				t_printf;

/*
** --------------------------- ft_printf main functions ------------------------
*/

int				ft_printf(const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);
char			*ft_sprintf(const char *format, ...);
void			parse_optionals(t_printf *p);
void			cs_not_found(t_printf *p);

/*
** --------------------------- number related functions ------------------------
** %d %D %i %f %F %b %B %o %O %u %U %h %H %a %A
*/

void			pf_putnb(t_printf *p);
void			pf_putnb_base(int base, t_printf *p);
void			itoa_printf(intmax_t d, t_printf *p, int len);
void			itoa_base_printf(uintmax_t d, int b, t_printf *p);
void			pf_putdouble(t_printf *p, int n);

/*
** --------------------------- number related functions ------------------------
**  %s %S %c %C
*/

void			pf_putstr(t_printf *p);
void			pf_putwstr(t_printf *p);
void			pf_character(t_printf *p, unsigned c);
void			pf_puterror(char *s, t_printf *p);

/*
** --------------------------- miscellaneous functions -------------------------
*/

void			buffer(t_printf *p, void *new, size_t size);
void			padding(t_printf *p, int n);
void			print_pointer_address(t_printf *p);

/*
** --------------------------- colors related defines --------------------------
*/

# define PF_RED			"\033[31m"
# define PF_GREEN		"\033[32m"
# define PF_YELLOW		"\033[33m"
# define PF_BLUE		"\033[34m"
# define PF_PURPLE		"\033[35m"
# define PF_CYAN		"\033[36m"
# define PF_EOC			"\033[36m"

#endif
