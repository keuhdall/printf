/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_addr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 12:45:04 by lmarques          #+#    #+#             */
/*   Updated: 2017/09/03 05:09:54 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi_parse(char **s)
{
	int		sign;
	int		r;

	r = 0;
	sign = 1;
	if (**s == '-' || **s == '+')
		sign = 44 - *(*s)++;
	while (**s >= '0' && **s <= '9')
		r = r * 10 + *(*s)++ - '0';
	return (sign * r);
}