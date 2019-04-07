/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 15:53:24 by jtsai             #+#    #+#             */
/*   Updated: 2018/08/30 10:42:39 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		type(int k)
{
	return (k == 's' || k == 'S' || k == 'p' || k == 'd' || k == 'D' || \
			k == 'i' || k == 'o' || k == 'O' || k == 'u' || k == 'U' || \
			k == 'x' || k == 'X' || k == 'c' || k == 'C' || k == '%' || \
			k == 'b' || k == 'r' || k < 32);
}

void	init_flags(t_var *data)
{
	int	j;

	j = 31;
	while (++j < 50)
		data->flag[j] = 0;
	data->flag['_'] = 0;
	data->flag['h'] = 0;
	data->flag['H'] = 0;
	data->flag['l'] = 0;
	data->flag['L'] = 0;
	data->flag['j'] = 0;
	data->flag['t'] = 0;
	data->flag['z'] = 0;
}

int		star_and_precision(t_var *data, char *s, int i)
{
	int	tmp;

	if (s[i] == '.')
	{
		data->flag['.'] = 1 | (++i & 0);
		if ('1' <= s[i] && s[i] <= '9')
			data->flag['/'] = re_atoi(s + i, &i);
		else if (s[i] == '*')
		{
			tmp = va_arg(data->args, int);
			data->flag['.'] = (tmp < 0) ? 0 : 1;
			tmp = (tmp >= 0) ? tmp : 0;
			data->flag['/'] = tmp | (++i & 0);
		}
	}
	else if (s[i] == '*')
	{
		tmp = va_arg(data->args, int);
		if (tmp < 0)
			data->flag['-'] = 1;
		tmp = (tmp >= 0) ? tmp : -tmp;
		data->flag['_'] = tmp | (++i & 0);
	}
	return (i);
}

int		read_flags(t_var *data, char *s, int i)
{
	init_flags(data);
	if (type(s[i]))
		return (i);
	while (!type(s[i]) && s[i])
	{
		if ('1' <= s[i] && s[i] <= '9')
			data->flag['_'] = re_atoi(s + i, &i);
		else if (s[i] == '*' || s[i] == '.')
			i = star_and_precision(data, s, i);
		else if (s[i] == 'h' && s[i + 1] == 'h')
		{
			data->flag['H'] = 1;
			i += 2;
		}
		else if (s[i] == 'l' || s[i] == 'h' || s[i] == 'j' ||
				s[i] == 'j' || s[i] == 't' || s[i] == 'z' ||
				s[i] == ' ' || s[i] == '+' || s[i] == '-' ||
				s[i] == '0' || s[i] == '#')
			data->flag[(t_long)s[i++]] = 1;
		else
			break ;
	}
	return (i);
}
