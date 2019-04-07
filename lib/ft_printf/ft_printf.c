/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 14:46:12 by jtsai             #+#    #+#             */
/*   Updated: 2018/08/24 11:14:54 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	read_string(t_var *data, char *s)
{
	int		i;

	data->return_value = 0;
	data->k = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\\' && s[i + 1] == '%')
			data->p[data->k++] = '%';
		else if (s[i] == '%')
		{
			i = read_flags(data, s, ++i);
			i = read_specifier(data, s[i], i);
		}
		else
			data->p[data->k++] = s[i];
		if (data->k > LEN)
		{
			write(1, data->p, data->k);
			data->return_value += data->k;
			i = -1;
		}
	}
}

int		ft_printf(const char *str, ...)
{
	char	*s;
	t_var	data;

	s = (char *)str;
	va_start(data.args, str);
	read_string(&data, s);
	write(1, data.p, data.k);
	data.return_value += (t_max)data.k;
	va_end(data.args);
	return (data.return_value);
}
