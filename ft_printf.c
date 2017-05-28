/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 15:55:16 by lmarques          #+#    #+#             */
/*   Updated: 2017/05/28 18:05:50 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	conv_1(const char *test)
{
	return ;
}

void	ft_init_struct(t_env *env)
{
	ft_strcpy(env->conv[0].flag, "bdiouxX");
	ft_strcpy(env->conv[1].flag, "DOU");
	ft_strcpy(env->conv[2].flag, "Cc");
	ft_strcpy(env->conv[3].flag, "s");
	ft_strcpy(env->conv[4].flag, "S");
	ft_strcpy(env->conv[5].flag, "p");
	ft_strcpy(env->conv[6].flag, "%");
	env->conv[0].ft_conv = conv_1;
	env->conv[1].ft_conv = conv_1;
	env->conv[2].ft_conv = conv_1;
	env->conv[3].ft_conv = conv_1;
	env->conv[4].ft_conv = conv_1;
	env->conv[5].ft_conv = conv_1;
}

void	ft_parse_flag(char *s)
{
	int	count;

	count = -1;
	if (!s)
		return ;
	while (s[++count])
	{
		ft_parse_modifier(s);
	}
}

void	ft_parse_format(char *s)
{
	int	count;

	count = -1;
	while (s[++count])
		if (s[count] == '%')
			ft_parse_flag(s + count + 1);
}

int		ft_printf(const char *format, ...)
{
	int			count;
	va_list		args;
	t_env		env;

	count = -1;
	va_start(args, format);
	while (++count < ft_atoi(format))
		ft_putstr(va_arg(args, char *));
	va_end(args);
	return (0);
}

int		main(void)
{
	ft_printf("ceci est %j %ll %h%hh un test%", 0);
	return (0);
}
