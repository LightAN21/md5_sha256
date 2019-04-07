/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_wide_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 16:30:50 by jtsai             #+#    #+#             */
/*   Updated: 2018/08/30 12:36:31 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	save_wide_char(t_var *data, wchar_t wc)
{
	if (wc <= 0x7F)
		data->p[data->k++] = wc;
	else if (wc <= 0x7FF)
	{
		data->p[data->k++] = ((wc >> 6) + 0xC0);
		data->p[data->k++] = ((wc & 0x3F) + 0x80);
	}
	else if (wc <= 0xFFFF)
	{
		data->p[data->k++] = ((wc >> 12) + 0xE0);
		data->p[data->k++] = (((wc >> 6) & 0x3F) + 0x80);
		data->p[data->k++] = ((wc & 0x3F) + 0x80);
	}
	else if (wc <= 0x10FFFF)
	{
		data->p[data->k++] = ((wc >> 18) + 0xF0);
		data->p[data->k++] = (((wc >> 12) & 0x3F) + 0x80);
		data->p[data->k++] = (((wc >> 6) & 0x3F) + 0x80);
		data->p[data->k++] = ((wc & 0x3F) + 0x80);
	}
}

t_long	ft_wide_strllen(wchar_t *s)
{
	t_long	len;
	t_long	i;

	len = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] <= 0x7F)
			len++;
		else if (s[i] <= 0x7FF)
			len += 2;
		else if (s[i] <= 0xFFFF)
			len += 3;
		else if (s[i] <= 0x10FFFF)
			len += 4;
	}
	return (len);
}

void	save_wide_str(t_var *data, wchar_t *ws)
{
	t_long	i;

	i = -1;
	while (ws[++i])
		save_wide_char(data, ws[i]);
}

void	deal_wide_char(t_var *data, wchar_t wc)
{
	int	w;

	if (data->flag['-'])
		save_wide_char(data, wc);
	w = data->flag['_'] - 1;
	if (w)
	{
		if (data->flag['0'] && !data->flag['-'])
			save_char(data, w, 0, '0');
		else
			save_char(data, w, 0, ' ');
	}
	if (!data->flag['-'])
		save_wide_char(data, wc);
}

void	deal_wide_string(t_var *data, wchar_t *ws)
{
	t_long	len;
	t_max	w;

	if (ws == NULL)
	{
		null_str(data);
		return ;
	}
	len = ft_wide_strllen(ws);
	if (data->flag['.'] && data->flag['/'] < len)
		len = data->flag['/'];
	if (data->flag['-'])
		save_wide_str(data, ws);
	w = data->flag['_'] - len;
	if (w > 0)
	{
		if (data->flag['0'] && !data->flag['-'])
			save_char(data, w, 0, '0');
		else
			save_char(data, w, 0, ' ');
	}
	if (!data->flag['-'])
		save_wide_str(data, ws);
}
