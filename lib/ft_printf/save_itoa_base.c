/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_itoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 21:34:57 by jtsai             #+#    #+#             */
/*   Updated: 2018/08/22 11:49:28 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	save_itoa_base(t_var *data, t_max num, t_max base, char c)
{
	t_max	len;
	t_max	tmp;
	int		start;
	char	*s;

	if (c != 'X')
		s = "0123456789abcdef";
	else
		s = "0123456789ABCDEF";
	tmp = num;
	len = 0;
	while (tmp)
		tmp /= base | (++len & 0);
	start = data->k;
	data->k += len + (num == 0);
	if (num == 0)
		data->p[start] = '0';
	while (len != 0)
	{
		data->p[start + (--len)] = s[num % base];
		num /= base;
	}
}
