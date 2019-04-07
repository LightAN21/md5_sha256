/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 10:31:40 by jtsai             #+#    #+#             */
/*   Updated: 2018/08/30 11:48:15 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	null_str(t_var *data)
{
	data->p[data->k++] = '(';
	data->p[data->k++] = 'n';
	data->p[data->k++] = 'u';
	data->p[data->k++] = 'l';
	data->p[data->k++] = 'l';
	data->p[data->k++] = ')';
}

t_long	ft_strllen(char *s)
{
	int len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	deal_char(t_var *data, int c)
{
	int	w;

	if (data->flag['-'])
		data->p[data->k++] = c;
	w = data->flag['_'] - 1;
	if (w)
	{
		if (data->flag['0'] && !data->flag['-'])
			save_char(data, w, 0, '0');
		else
			save_char(data, w, 0, ' ');
	}
	if (!data->flag['-'])
		data->p[data->k++] = c;
}

void	deal_str(t_var *data, char *s)
{
	t_long	len;
	t_max	w;

	if (s == NULL && !(data->flag['.']))
	{
		null_str(data);
		return ;
	}
	if (s)
		len = ft_strllen(s);
	if (data->flag['.'] && data->flag['/'] < len)
		len = data->flag['/'];
	if (data->flag['-'])
		save_str(data, s, len);
	w = data->flag['_'] - len;
	if (w > 0)
	{
		if (data->flag['0'] && !data->flag['-'])
			save_char(data, w, 0, '0');
		else
			save_char(data, w, 0, ' ');
	}
	if (!data->flag['-'] && s != NULL)
		save_str(data, s, len);
}

void	deal_l_str(t_var *data, wchar_t *s)
{
	t_long	len;
	t_max	w;

	if (s == NULL && !(data->flag['.']))
	{
		null_str(data);
		return ;
	}
	if (s)
		len = ft_wide_strllen(s);
	if (data->flag['.'] && data->flag['/'] < len)
		len = data->flag['/'];
	if (data->flag['-'])
		save_l_str(data, s, len);
	w = data->flag['_'] - len;
	if (w > 0)
	{
		if (data->flag['0'] && !data->flag['-'])
			save_char(data, w, 0, '0');
		else
			save_char(data, w, 0, ' ');
	}
	if (!data->flag['-'] && s != NULL)
		save_l_str(data, s, len);
}
