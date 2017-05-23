/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 15:55:16 by lmarques          #+#    #+#             */
/*   Updated: 2017/05/23 19:00:28 by lmarques         ###   ########.fr       */
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
		if (++format && *format == 'h')
			flag->modifiers.h = 2;
	}
	else if (*format == 'l')
	{
		flag->modifiers.l = 1;
		if (++format && *format == 'l')
			flag->modifiers.l = 2;
	}
}

void	ft_fill_flags(char *format, t_flag_lst **lst)
{
	int		count;
	t_flag	flag;

	count = -1;
	ft_bzero(&flag, sizeof(flag));
	while (format[++count])
	{
		if (format[count] == '%')
		{
			ft_parse_modifiers(format + count + 1, &flag);
			ft_push_flag(lst, ft_new_flag(flag));
		}
	}
}

int		ft_printf(const char *format, ...)
{
	int			count;
	va_list		args;
	t_flag_lst	*lst;

	lst = NULL;
	ft_fill_flags((char *)format, &lst);
	count = -1;
	va_start(args, format);
	while (++count < ft_atoi(format))
		ft_putstr(va_arg(args, char*));
	va_end(args);
	while (lst)
	{
		printf("modifier z = %d\n", lst->flag.modifiers.z);
		printf("modifier j = %d\n", lst->flag.modifiers.j);
		printf("modifier # = %d\n", lst->flag.modifiers.sharp);
		printf("modifier 0 = %d\n", lst->flag.modifiers.zero);
		printf("modifier - = %d\n", lst->flag.modifiers.minus);
		printf("modifier + = %d\n", lst->flag.modifiers.plus);
		printf("modifier h = %d\n", lst->flag.modifiers.h);
		printf("modifier l = %d\n", lst->flag.modifiers.l);
		printf("------------------\n");
		lst = lst->next;
	}
	return (0);
}

int		main(void)
{
	ft_printf("ceci est %j %ll %h%hh un test%", 0);
	return (0);
}
