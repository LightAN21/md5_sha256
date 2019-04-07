/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha2_64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 12:19:04 by jtsai             #+#    #+#             */
/*   Updated: 2019/03/12 12:20:26 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		append_message_512(t_info *info, uint64_t *w, int len)
{
	int	i;
	int	j;

	if (info->flag['p'] && info->fd == 0 && !info->flag['s'])
		write(1, info->chunk, len);
	j = len >> 3;
	if (len & 7)
	{
		info->chunk[len] = 0x80;
		i = len;
		while (((++i) & 7))
			info->chunk[i] = 0;
	}
	else
		w[j] = 0x80;
	while ((++j & 15) != 14)
		w[j] = 0;
	w[j++] = 0;
	w[j++] = reverse_word((info->total_len << 3));
	sha512_process(info, w, (len >> 7) + (((len & 127) >= 112) ? 2 : 1));
}

void		sha512_hash_string(t_info *info, char *s)
{
	uint64_t	i;
	uint64_t	j;
	uint64_t	len;

	init_64(info);
	len = ft_strlen(s);
	info->total_len = len;
	if (len >> 7)
	{
		sha512_process(info, (uint64_t *)s, (len >> 7));
		i = 0;
		j = ((len >> 7) << 7);
		while (j < len)
			info->chunk[i++] = s[j++];
		len -= ((len >> 7) << 7);
	}
	else
	{
		i = -1;
		while (++i < len)
			info->chunk[i] = s[i];
	}
	append_message_512(info, (uint64_t *)(info->chunk), len);
	print_result(info, s);
}

int			hand_stdin_512(t_info *info, int tmp_len)
{
	int	len;
	int	tmp;

	len = ((tmp_len >> 7) << 7);
	tmp = 0;
	while (len < tmp_len)
		info->chunk[tmp++] = info->chunk[len++];
	tmp_len -= ((tmp_len >> 7) << 7);
	info->tmp = info->chunk + tmp_len;
	return (tmp_len);
}

void		sha512_hash_file(t_info *info, char *path)
{
	int	len;
	int	tmp_len;

	init_64(info);
	tmp_len = 0;
	while ((len = read(info->fd, info->tmp, CHUNK_SIZE)) > 0)
	{
		info->total_len += (uint64_t)len;
		tmp_len += len;
		if (tmp_len >= CHUNK_SIZE)
		{
			if (info->fd == 0 && info->flag['p'] && !info->flag['s'])
				write(1, info->chunk, ((tmp_len >> 7) << 7));
			sha512_process(info, (uint64_t *)(info->chunk), (tmp_len >> 7));
			tmp_len = (tmp_len == CHUNK_SIZE) ?\
				0 : hand_stdin_512(info, tmp_len);
		}
		else
			info->tmp += len;
	}
	append_message_512(info, (uint64_t *)(info->chunk), tmp_len);
	print_result(info, path);
}
