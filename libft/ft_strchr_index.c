/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarques <lmarques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 20:13:57 by lmarques          #+#    #+#             */
/*   Updated: 2017/09/03 05:13:19 by lmarques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strchr_index(char *s, int c)
{
	int	count;

	count = -1;
	while (s[++count])
	{
		if (s[count] == c)
			return (count);
	}
	return (-1);
}
