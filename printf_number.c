/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_number.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 06:02:33 by lmarques          #+#    #+#             */
/*   Updated: 2017/09/03 06:24:52 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		pf_putnb(t_printf *p)
{
	intmax_t	n;

	if (p->f & FL_LONG || p->f & FL_LONG2)
		n = (p->f & FL_LONG2) ? ((intmax_t)va_arg(p->lst, long long)) :
			((intmax_t)va_arg(p->lst, long));
	else if (p->f & FL_SHORT || p->f & FL_SHORT2)
		n = (p->f & FL_SHORT2) ? (intmax_t)((char)va_arg(p->lst, int)) :
			(intmax_t)((short)va_arg(p->lst, int));
	else if (p->f & FL_INTMAX)
		n = (va_arg(p->lst, intmax_t));
	else if (p->f & FL_SIZE_T)
		n = ((intmax_t)va_arg(p->lst, ssize_t));
	else
		n = ((intmax_t)va_arg(p->lst, int));
	(p->f & FL_ZERO) ? p->accu = p->min_len : 0;
	itoa_printf(n, p, 0);
}

void		pf_putnb_base(int base, t_printf *p)
{
	uintmax_t	n;

	if (p->f & FL_LONG || p->f & FL_LONG2)
		n = (p->f & FL_LONG2) ? ((intmax_t)va_arg(
			p->lst, unsigned long long)) :
			((intmax_t)va_arg(p->lst, unsigned long));
	else if (p->f & FL_SHORT || p->f & FL_SHORT2)
		n = (p->f & FL_SHORT2) ? (uintmax_t)((unsigned char)va_arg(p->lst, int))
			: (uintmax_t)((unsigned short)va_arg(p->lst, int));
	else if (p->f & FL_INTMAX)
		n = (va_arg(p->lst, uintmax_t));
	else if (p->f & FL_SIZE_T)
		n = ((uintmax_t)va_arg(p->lst, size_t));
	else
		n = (uintmax_t)va_arg(p->lst, unsigned int);
	itoa_base_printf(n, base, p);
}

static void	itoa_base_fill(uintmax_t tmp, int b, char s[PF_BUF_SIZE],
	t_printf *p)
{
	int		len;

	if (tmp && !(p->f & FL_POINTER) && (p->f & FL_ZERO) &&
		(p->f & FL_SHARP) && b == 16 && !(p->f & FL_LONG2) &&
		p->printed > 3)
		p->printed -= 2;
	len = p->printed;
	p->c = 'a' - 10 - ((p->f & FL_UPCASE) >> 1);
	while (len--)
	{
		s[len] = tmp % b + ((tmp % b < 10) ? '0' : p->c);
		tmp /= b;
	}
	(p->f & FL_APP_ACCU && p->f & FL_ZERO) ? s[0] = ' ' : 0;
}

void		itoa_printf(intmax_t n, t_printf *p, int len)
{
	char		s[21];
	uintmax_t	tmp;

	tmp = n < 0 ? -n : n;
	while (tmp)
	{
		tmp /= 10;
		++len;
	}
	if ((n < 0 || p->f & FL_PLUS || p->f & FL_SPACE) && p->f & FL_ZERO)
		--p->accu;
	p->printed = MAX(len, p->accu);
	if (n < 0 || p->f & FL_PLUS || p->f & FL_SPACE)
		++p->printed;
	p->padding = (p->printed > p->min_len) ? 0 : p->min_len - p->printed;
	padding(p, 0);
	tmp = n < 0 ? -n : n;
	itoa_base_fill(tmp, 10, s, p);
	(p->f & FL_SPACE) ? s[0] = ' ' : 0;
	(n < 0) ? s[0] = '-' : 0;
	(p->f & FL_PLUS && n >= 0) ? s[0] = '+' : 0;
	buffer(p, s, p->printed);
	padding(p, 1);
}

void		itoa_base_printf(uintmax_t n, int b, t_printf *p)
{
	uintmax_t	tmp;
	char		s[21];
	int			ext;

	p->printed = 0;
	tmp = n;
	while (tmp && ++p->printed)
		tmp /= b;
	(p->f & FL_ZERO) ? p->accu = p->min_len : 0;
	ext = (p->printed >= p->accu) ? 0 : 1;
	p->printed = MAX(p->accu, p->printed);
	((p->f & FL_SHARP) && b == 8 && !ext) ? --p->min_len : 0;
	((p->f & FL_SHARP) && b == 8 && !n && (p->f & FL_APP_ACCU)) ?
	++p->printed : 0;
	((p->f & FL_SHARP) && b == 16 && !(p->f & FL_ZERO)) ? p->min_len -= 2 : 0;
	p->padding = MAX(0, (p->min_len - p->printed));
	padding(p, 0);
	if ((n || (p->f & FL_POINTER)) && (p->f & FL_SHARP) &&
		((b == 8 && !ext) || (b == 16)))
		buffer(p, "0", 1);
	if ((n || (p->f & FL_POINTER)) && (p->f & FL_SHARP) && b == 16)
		buffer(p, (p->f & FL_UPCASE) ? "X" : "x", 1);
	itoa_base_fill(n, b, s, p);
	buffer(p, s, p->printed);
	padding(p, 1);
}
