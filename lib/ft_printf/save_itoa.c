/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_itoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 08:20:42 by jtsai             #+#    #+#             */
/*   Updated: 2018/08/25 16:35:12 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	save_itoa(t_var *data, int k, t_long num)
{
	t_long	len;
	t_long	tmp;

	tmp = num;
	len = 1;
	while (tmp /= 10)
		++len;
	data->k += len;
	if (num >= 0)
		tmp++;
	else
		tmp--;
	while (--len > 0)
	{
		data->p[k + len] = '0' + tmp * (num % 10);
		num /= 10;
	}
	if (data->flag['_'] && !data->flag['/'] && num == 0)
		data->p[k] = ' ';
	else
		data->p[k] = '0' + num * tmp;
}
