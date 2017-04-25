/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 15:55:16 by lmarques          #+#    #+#             */
/*   Updated: 2017/04/25 17:48:22 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
