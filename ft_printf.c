/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 15:55:16 by lmarques          #+#    #+#             */
/*   Updated: 2017/04/27 19:38:28 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	ft_parse_modifiers(char *format, t_flag *flag)
{
	if (*format == 'z')
		flag->modifiers.z = 1;
	else if (*format == 'j')
		flag->modifiers.z = 1;
	else if (*format == '#')
		flag->modifiers.sharp = 1;
	else if (*format == '0')
		flag->modifiers.zero = 1;
	else if (*format == '-')
		flag->modifiers.minus = 1;
	else if (*format == '+')
		flag->modifiers.plus = 1;
	else if (*format == 'h')
	{
		flag->modifiers.h = 1;
		if (++*format && *format == 'h')
			flag->modifiers.h = 2;
	}
	else if (*format == 'l')
	{
		flag->modifiers.l = 1;
		if (++*format && *format == 'l')
			flag->modifiers.l = 2;
	}
}

void	ft_fill_flags(char *format, t_flag_lst *lst)
{
	int		count;
	t_flag	flag;

	count = -1;
	ft_bzero(&flag, sizeof(flag));
	while (format[++count])
	{
		if (format[count] == '%')
		{
			ft_parse_modifiers(format, &flag);
		}
	}
}

int		ft_printf(const char *format, ...)
{
	int			count;
	va_list		args;
	t_flag_lst	*lst;

	count = -1;
	va_start(args, format);
	while (++count < ft_atoi(format))
		ft_putstr(va_arg(args, char*));
	va_end(args);
	return (0);
}

int		main(void)
{
	ft_printf("5", "test1", "test2", "test3", "test4", "test5");
	return (0);
}
