/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 15:55:28 by lmarques          #+#    #+#             */
/*   Updated: 2017/05/28 18:07:32 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "./libft/libft.h"

#define STRUCT_SIZE 7

typedef struct			s_conv
{
	char				flag[8];
	void				(*ft_conv)(const char *);
}						t_conv;

typedef struct			s_modifier
{
	char				h;
	char				l;
	char				j;
	char				z;
	char				sharp;
	char				zero;
	char				minus;
	char				plus;
}						t_modifier;

typedef struct			s_flag
{
	char				rule;
	t_modifier			modifier;
}						t_flag;

typedef struct			s_flag_lst
{
	t_flag				flag;
	struct s_flag_lst	*next;
}						t_flag_lst;

typedef struct			s_env
{
	t_flag_lst			flag_list;
	t_conv				conv[STRUCT_SIZE];
}						t_env;

#endif
