/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 08:59:27 by jtsai             #+#    #+#             */
/*   Updated: 2018/08/25 19:30:50 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	save_char(t_var *data, t_long bound, t_long mark, char c)
{
	int		i;
	char	tmp[10000];

	i = 0;
	if (bound > 10000)
	{
		write(1, data->p, data->k);
		data->k = 0;
		while (i < 10000)
			tmp[i++] = c;
		i = 10000;
		while (i < bound)
		{
			write(1, tmp, 10000);
			i += 10000;
			data->k += 10000;
		}
		i -= 10000;
	}
	if (mark && (data->flag['+'] || data->flag[' ']))
		i++;
	while (++i <= bound)
		data->p[data->k++] = c;
}
