/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 09:54:44 by jtsai             #+#    #+#             */
/*   Updated: 2018/08/30 11:30:05 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	save_str(t_var *v, char *s, t_long len)
{
	t_long	i;

	i = -1;
	while (++i < len)
	{
		v->p[v->k++] = s[i];
		if (v->k >= 10000)
		{
			write(1, v->p, v->k);
			v->return_value += v->k;
			v->k = 0;
		}
	}
}

void	save_l_str(t_var *v, wchar_t *s, t_long len)
{
	t_long	i;

	i = -1;
	while (++i < len)
		v->p[v->k++] = s[i];
}
