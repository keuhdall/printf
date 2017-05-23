/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 19:07:54 by lmarques          #+#    #+#             */
/*   Updated: 2017/05/01 16:58:08 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flag_lst	*ft_new_flag(t_flag flag)
{
	t_flag_lst	*tmp;
	if (!(tmp = (t_flag_lst *)malloc(sizeof(t_flag_lst))))
		return (NULL);
	tmp->flag = flag;
	tmp->next = NULL;
	return (tmp);
}

void		ft_push_flag(t_flag_lst **list, t_flag_lst *new)
{
	t_flag_lst	*tmp;

	tmp = NULL;
	tmp = *list;
	if (!tmp)
		*list = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
