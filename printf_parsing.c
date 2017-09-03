/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 06:02:43 by lmarques          #+#    #+#             */
/*   Updated: 2017/09/03 05:19:42 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

/*
** 						~ FLAGS ~
**
** flags interract between them, if there is a minus then it
** cancels the zero flag. if there is a + it cancels the sp flag.
** sharp is to add the prefix 0x for hexa for example
*/

static void	parse_flags(t_printf *p)
{
	while ((p->n = ft_strchr_index("# +-0*", *p->format)) > -1 && ++p->format)
		p->f |= (1 << p->n);
	((p->f & FL_MINUS) && !(p->f & FL_WILDCARD)) ? p->f &= ~FL_ZERO : 0;
	(p->f & FL_PLUS) ? p->f &= ~FL_SPACE : 0;
	if (p->f & FL_WILDCARD)
	{
		p->f &= ~FL_WILDCARD;
		if ((p->n = (int)va_arg(p->lst, int)) < 0)
		{
			p->f |= FL_MINUS;
			p->n = -p->n;
		}
		else
			p->f &= ~FL_MINUS;
		if (!(p->f & FL_APP_ACCU))
			p->min_len = p->n;
		else
		{
			p->accu = (!(p->f & FL_MINUS)) ? p->n : 0;
			p->f = (!p->n) ? p->f | FL_APP_ACCU : p->f & ~FL_APP_ACCU;
		}
	}
}

/*
** 						~ FIELD WIDTH ~
** if (48 < *p->format && *p->format < 58)
** An optional decimal digit string (with nonzero first digit) specifying a
** minimum field width. If the converted value has fewer characters than the
** field width, it will be padded with spaces on the left (or right, if the
** left-adjustment flag has been given). Instead of a decimal digit string
** one may write "*" or "*m$" (for some decimal integer m) to specify that
** the field width is given in the next argument, or in the m-th argument,
** respectively, which must be of type int. A negative field width is taken
** as a '-' flag followed by a positive field width. In no case does a
** nonexistent or small field width cause truncation of a field; if the result
** of a conversion is wider than the field width, the field is expanded to
** contain the conversion result.
**
** 2nd if : if there is a conv. specifier after the field width for a base it
** will reset the min_len to 0 EXCEPT if it was a padding with 0s ...
**
** 49 is ASCII for 1 and 57 for 9
*/

/*
** 						~ PRECISION ~
** if (*p->format == '.')
** An optional precision, in the form of a period ('.') followed by an optional
** decimal digit string. Instead of a decimal digit string one may write "*" or
** "*m$" (for some decimal integer m) to specify that the precision is given in
** the next argument, or in the m-th argument, respectively, which must be of
** type int. If the precision is given as just '.', or the precision is
** negative, the precision is taken to be zero. This gives the minimum number
** of digits to appear for d, i, o, u, x, and X conversions, the number of
** digits to appear after the radix character for a, A, e, E, f, and F
** conversions, the maximum number of significant digits for g and G
** conversions, or the maximum number of characters to be printed from a
** string for s and S conversions.
*/

/*
** 						~ LENGTH MODIFIER ~
** while (ft_strchr("hljzL", *p->format))
** converts into short, shortshort, long, long long, int_max, size_t depending
** on the input, respectively : h, hh, l, ll, j, z
*/

static int	ft_max(int a, int b)
{
	return (a > b ? a : b);
}

static void	field_width_precision(t_printf *p)
{
	if (48 < *p->format && *p->format < 58)
		p->min_len = ft_max(ft_atoi_addr(&p->format), 1);
	if (*p->format == '.')
	{
		++p->format;
		p->accu = ft_max(ft_atoi_addr(&p->format), 0);
		p->f |= FL_APP_ACCU;
	}
	while (1)
	{
		if (*p->format == 'h')
			p->f |= (p->format[1] == 'h' && ++p->format) ? FL_SHORT2 : FL_SHORT;
		else if (*p->format == 'l')
			p->f |= (p->format[1] == 'l' && ++p->format) ? FL_LONG2 : FL_LONG;
		else if (*p->format == 'j')
			p->f |= FL_INTMAX;
		else if (*p->format == 'z')
			p->f |= FL_SIZE_T;
		else if (*p->format == 'L')
			p->f |= FL_LONG2;
		else
			break ;
		++p->format;
	}
}

/*
** 						~ CONVERSION SPECIFIER ~
**
** A character that specifies the type of conversion to be applied
** if the character following % is a % then is it acts as an ESC char
** The conversion specifiers and their meanings are:
** 1) d, i, D : signed int
** 2) o, u, x, X : unsigned octal, uns. decimal, uns. hexa lower and uppercase
** 3) b, B for unsigned binary
** 3) c, C : char and large char
** 4) s : pointer to a string
** 5) n : the number of characters written so far is stored into the integer
** indicated by the int * pointer argument. No argument is converted.
** 6) m : Print output of strerror(errno). no arg. required
** 7) {} : adds color
** if the character is uppercase then p->cs.uppercase will be set to 1.
*/

static void	conversion_specifier(t_printf *p)
{
	if (ft_strchr_index("CDSUOBX", p->c) > -1)
		p->f |= (p->c != 'X') ? FL_LONG : FL_UPCASE;
	if (p->c == 's')
		(p->f & FL_LONG || p->f & FL_LONG2) ? pf_putwstr(p) : pf_putstr(p);
	else if (p->c == 'd' || p->c == 'i' || p->c == 'D')
		pf_putnb(p);
	else if (p->c == 'f' || p->c == 'F')
		(p->f & FL_APP_ACCU && !p->accu) ? pf_putnb(p) : pf_putdouble(p, 10);
	else if ((p->printed = ft_strchr_index("dDbBdDdDoOuUdDdDxX", p->c)) > -1)
		pf_putnb_base(p->printed & ~1, p);
	else if (p->c == 'c' || p->c == 'C')
		pf_character(p, va_arg(p->lst, unsigned));
	else if (p->c == 'S')
		pf_putwstr(p);
	else if (p->c == 'p')
		print_pointer_address(p);
	else if (p->c == 'n')
		*va_arg(p->lst, int *) = p->len;
	else if (p->c == 'm')
		pf_puterror(strerror(errno), p);
	else if (p->c == 'a' || p->c == 'A')
		(p->f & FL_APP_ACCU && !p->accu) ? pf_putnb(p) : pf_putdouble(p, 16);
	else
		cs_not_found(p);
	p->len > 0 ? p->i = 0 : 0;
}

/*
** 						~ PARSING OPTONAL INPUTS ~
**
** here we parse the % to check for optional inputs :
** 1) flags, 2) field width, 3) precision and 4) length modifiers.
** Please refer to the man for a more accurate and full description.
** 5) the call to wildcard_length_modifier is a bonus where the '*' given
** the field_width or precision in the va_list ap.
** 6) the second call to parse_flags is to handle undefined behaviors.
*/

void		parse_optionals(t_printf *p)
{
	p->f = 0;
	p->min_len = 0;
	p->accu = 1;
	parse_flags(p);
	field_width_precision(p);
	parse_flags(p);
	(p->f & FL_PLUS) ? p->f &= ~FL_SPACE : 0;
	p->c = *p->format;
	conversion_specifier(p);
}
