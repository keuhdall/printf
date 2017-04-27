/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 15:55:16 by lmarques          #+#    #+#             */
/*   Updated: 2017/04/27 03:48:06 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		ft_is_handled_option(char c)
{
	if (c == '%' || c == 'd' || c == 's' || c == 'c')
		return (1);
	else
		return (0);
}

int		ft_count_flags(const char *format)
{
	int	count;
	int	count_flags;

	count = -1;
	count_flags = 0;
	while (format[++count])
	{
		if (format[count] == '%')
		{
			if (!format[count + 1] || !ft_is_handled_option(format[count + 1]))
				exit(-1);
			else
				++count_flags;
		}
	}
	return (count_flags);
}

int		ft_printf(const char *format, ...)
{
	int		count;
	va_list	args;

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
