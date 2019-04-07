/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha2_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 12:17:09 by jtsai             #+#    #+#             */
/*   Updated: 2019/03/12 12:24:42 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		append_message_256(t_info *info, uint32_t *w, int len)
{
	int			j;
	uint32_t	tmp;

	if (info->flag['p'] && info->fd == 0 && !info->flag['s'])
		write(1, info->chunk, len);
	j = len >> 2;
	if (len & 3)
		w[j] = (w[j] & ((1 << ((len & 3) << 3)) - 1)) +\
			(0x80 << ((len & 3) << 3));
	else
		w[j] = 0x80;
	while ((++j & 15) != 14)
		w[j] = 0x00000000;
	tmp = (info->total_len >> 29);
	w[j++] = ((tmp & 0xff) << 24) + ((tmp & 0xff00) << 8) +\
			((tmp & 0xff0000) >> 8) + ((tmp & 0xff000000) >> 24);
	tmp = ((info->total_len << 3) & 0xffffffff);
	w[j++] = ((tmp & 0xff) << 24) + ((tmp & 0xff00) << 8) +\
			((tmp & 0xff0000) >> 8) + ((tmp & 0xff000000) >> 24);
	sha256_process(info, w, (len >> 6) + (((len & 63) >= 56) ? 2 : 1));
}

void		sha256_hash_string(t_info *info, char *s)
{
	uint32_t	i;
	uint64_t	j;
	uint64_t	len;

	init_32(info);
	len = ft_strlen(s);
	info->total_len = len;
	if (len >> 6)
	{
		sha256_process(info, (uint32_t *)s, (len >> 6));
		i = 0;
		j = ((len >> 6) << 6);
		while (j < len)
			info->chunk[i++] = s[j++];
		len -= ((len >> 6) << 6);
	}
	else
	{
		i = -1;
		while (++i < len)
			info->chunk[i] = s[i];
	}
	append_message_256(info, (uint32_t *)(info->chunk), len);
	print_result(info, s);
}

int			hand_stdin_256(t_info *info, int tmp_len)
{
	int	len;
	int	tmp;

	len = ((tmp_len >> 6) << 6);
	tmp = 0;
	while (len < tmp_len)
		info->chunk[tmp++] = info->chunk[len++];
	tmp_len -= ((tmp_len >> 6) << 6);
	info->tmp = info->chunk + tmp_len;
	return (tmp_len);
}

void		sha256_hash_file(t_info *info, char *path)
{
	int			len;
	int			tmp_len;

	init_32(info);
	tmp_len = 0;
	while ((len = read(info->fd, info->tmp, CHUNK_SIZE)) > 0)
	{
		info->total_len += (uint64_t)len;
		tmp_len += len;
		if (tmp_len >= CHUNK_SIZE)
		{
			if (info->flag['p'] && info->fd == 0 && !info->flag['s'])
				write(1, info->chunk, ((tmp_len >> 6) << 6));
			sha256_process(info, (uint32_t *)(info->chunk), (tmp_len >> 6));
			tmp_len = (tmp_len == CHUNK_SIZE) ?\
				0 : hand_stdin_256(info, tmp_len);
		}
		else
			info->tmp += len;
	}
	append_message_256(info, (uint32_t *)(info->chunk), tmp_len);
	print_result(info, path);
}
