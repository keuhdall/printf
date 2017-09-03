/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 19:18:44 by lmarques          #+#    #+#             */
/*   Updated: 2017/09/03 06:24:28 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** main function : printf will return the total len of chars displayed by printf
*/

int		ft_printf(const char *format, ...)
{
	t_printf	p;

	ft_bzero(&p, sizeof(p));
	p.fd = 1;
	p.format = (char *)format;
	va_start(p.lst, format);
	while (*p.format && p.len > -1)
	{
		if (*p.format == '%')
		{
			++p.format;
			if (!*p.format || (*p.format == ' ' && (!p.format[1]
			|| (!p.format[2] && p.format[1] == 'h'))))
				break ;
			else
				parse_optionals(&p);
		}
		else if (++p.i)
			buffer(&p, &*p.format, 1);
		++p.format;
	}
	(p.len < 0) ? write(p.fd, p.buff, p.buff_index - p.i)
		: write(p.fd, p.buff, p.buff_index);
	va_end(p.lst);
	return (p.len);
}

/*
** bonus function to specify a specific fd, similar to libc dprintf
*/

int		ft_dprintf(int fd, const char *format, ...)
{
	t_printf	p;

	ft_bzero(&p, sizeof(p));
	p.fd = fd;
	p.format = (char *)format;
	va_start(p.lst, format);
	while (*p.format && p.len > -1)
	{
		if (*p.format == '%')
		{
			++p.format;
			if (!*p.format || (*p.format == ' ' && (!p.format[1]
			|| (!p.format[2] && p.format[1] == 'h'))))
				break ;
			else
				parse_optionals(&p);
		}
		else if (++p.i)
			buffer(&p, &*p.format, 1);
		++p.format;
	}
	(p.len < 0) ? write(p.fd, p.buff, p.buff_index - p.i)
		: write(p.fd, p.buff, p.buff_index);
	va_end(p.lst);
	return (p.len);
}

/*
** sprintf returns the string
** Caution : intended for string < 64 (BUFF in define) characters.
*/

char	*ft_sprintf(const char *format, ...)
{
	t_printf	p;
	char		*ret;

	ft_bzero(&p, sizeof(p));
	p.fd = 1;
	p.format = (char *)format;
	va_start(p.lst, format);
	while (*p.format && p.len > -1)
	{
		if (*p.format == '%')
			parse_optionals(&p);
		else if (++p.i)
			buffer(&p, &*p.format, 1);
		++p.format;
	}
	p.buff[p.buff_index + 1] = '\0';
	if (!(ret = ft_strdup(p.buff)))
		return (NULL);
	va_end(p.lst);
	return (ret);
}

/*
** function that displays pointer address
*/

void	print_pointer_address(t_printf *p)
{
	void	*pointer;

	pointer = va_arg(p->lst, void *);
	p->f &= ~FL_SHARP;
	p->min_len -= (p->f & FL_ZERO ? 2 : 0);
	p->padding = (p->printed > p->min_len - 3) ? 0 :
		p->min_len - 3 - p->printed;
	p->f |= FL_SHARP;
	p->f |= FL_POINTER;
	p->printed = 0;
	itoa_base_printf((uintmax_t)pointer, 16, p);
}

/*
** function if no conversion specifier was found.
*/

void	cs_not_found(t_printf *p)
{
	if ((p->padding = p->min_len - 1) > 0)
	{
		padding(p, 0);
		buffer(p, p->format, 1);
		padding(p, 1);
	}
	else
		buffer(p, p->format, 1);
}
