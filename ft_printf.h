/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 15:55:28 by lmarques          #+#    #+#             */
/*   Updated: 2017/04/27 19:15:19 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "./libft/libft.h"

typedef struct			s_modifers
{
	char				h;
	char				l;
	char				j;
	char				z;
	char				sharp;
	char				zero;
	char				minus;
	char				plus;
	char				space;
}						t_modifiers;

typedef struct			s_flag
{
	size_t				pos;
	t_modifiers			modifiers;
	void				*content;
}						t_flag;

typedef struct			s_flag_lst
{
	t_flag				flag;
	struct s_flag_lst	*next;
}						t_flag_lst;

t_flag_lst				ft_new_flag(t_flag flag);
void					ft_push_flag(t_flag_lst **list, t_flag_lst *new);

#endif
