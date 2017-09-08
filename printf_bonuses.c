/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_bonuses.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 06:02:21 by lmarques          #+#    #+#             */
/*   Updated: 2017/09/08 20:06:11 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** bonuses done :
**   1) *   wildcard_length_modifier
**   2) n   print_len (refer to ft_printf.c : *va_arg(ap, int *) = p->len;)
**   3) m   ft_printf_putstr(strerror(errno), p)
**   4) {}  color
**   5) fF  ldtoa
*/

static double	ft_dabs(double n)
{
	return (n < 0 ? -n : n);
}

/*
** bonus function that handles float
** calculates the size of what should be sent to the buffer
** the decimals are calculated with p->accu
** decimal is first calculated as the right part, then we multiply it by
** 10 power p->accu + 1 in order to get the rounding.
*/

static void		ldtoa_fill(double n, t_printf *p, long value, int b)
{
	int		len;
	char	s[48];

	p->c = 'a' - 10 - ((p->f & FL_UPCASE) >> 1);
	len = p->printed - 1 - p->accu;
	while (p->accu--)
	{
		s[len + p->accu + 1] = value % b + ((value % b < 10) ? '0' : p->c);
		value /= b;
	}
	s[len] = '.';
	value = (long)(n < 0 ? -n : n);
	while (++p->accu < len)
	{
		s[len - p->accu - 1] = value % b + ((value % b < 10) ? '0' : p->c);
		value /= b;
	}
	(p->f & FL_APP_ACCU && p->f & FL_ZERO) ? s[0] = ' ' : 0;
	(p->f & FL_SPACE) ? s[0] = ' ' : 0;
	(n < 0) ? s[0] = '-' : 0;
	(p->f & FL_PLUS && n >= 0) ? s[0] = '+' : 0;
	if (b == 16 && (p->len += 2))
		buffer(p, "0x", 2);
	buffer(p, s, p->printed);
}

void			pf_putdouble(t_printf *p, int base)
{
	double		n;
	long		tmp;
	int			len;
	double		decimal;
	long		value;

	n = (double)va_arg(p->lst, double);
	(p->f & FL_ZERO) ? p->accu = p->min_len : 0;
	if (!(p->f & FL_APP_ACCU))
		p->accu = DEFAULT_ACCU + base - 10 + 1;
	len = 1;
	tmp = (long)(n < 0 ? -n : n);
	while (tmp && ++len)
		tmp /= base;
	p->printed = p->accu + len + ((n < 0) ? 1 : 0);
	decimal = ft_dabs(n);
	decimal = (decimal - (long)(ft_dabs(n))) * ft_pow(base, p->accu + 1);
	decimal = ((long)decimal % base > 4) ? decimal / base + 1 : decimal / base;
	value = (long)decimal;
	ldtoa_fill(n, p, value, base);
}

void			buffer(t_printf *p, void *new, size_t size)
{
	long		new_i;
	int			diff;

	new_i = 0;
	while (PF_BUF_SIZE - p->buff_index < size)
	{
		diff = PF_BUF_SIZE - p->buff_index;
		ft_memcpy(&(p->buff[p->buff_index]), &(new[new_i]), diff);
		size -= diff;
		new_i += diff;
		p->buff_index += diff;
		p->len += diff;
		write(p->fd, p->buff, p->buff_index);
		p->buff_index = 0;
	}
	ft_memcpy(&(p->buff[p->buff_index]), &(new[new_i]), size);
	p->buff_index += size;
	p->len += size;
}

/*
** 32 is ascii for space and 48 for 0, flag 0 is 16 bits if set.
*/

void			padding(t_printf *p, int n)
{
	if (p->padding)
	{
		p->c = 32 | (p->f & FL_ZERO);
		if (!n && !(p->f & FL_MINUS))
			while (p->padding--)
				buffer(p, &p->c, 1);
		else if (n && (p->f & FL_MINUS))
			while (p->padding--)
				buffer(p, &p->c, 1);
	}
}
