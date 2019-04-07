/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 11:27:27 by jtsai             #+#    #+#             */
/*   Updated: 2019/03/12 13:20:14 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_dispatch			g_d[64] =
{
	{0xd76aa478, 7}, {0xe8c7b756, 12}, {0x242070db, 17}, {0xc1bdceee, 22},
	{0xf57c0faf, 7}, {0x4787c62a, 12}, {0xa8304613, 17}, {0xfd469501, 22},
	{0x698098d8, 7}, {0x8b44f7af, 12}, {0xffff5bb1, 17}, {0x895cd7be, 22},
	{0x6b901122, 7}, {0xfd987193, 12}, {0xa679438e, 17}, {0x49b40821, 22},
	{0xf61e2562, 5}, {0xc040b340, 9}, {0x265e5a51, 14}, {0xe9b6c7aa, 20},
	{0xd62f105d, 5}, {0x02441453, 9}, {0xd8a1e681, 14}, {0xe7d3fbc8, 20},
	{0x21e1cde6, 5}, {0xc33707d6, 9}, {0xf4d50d87, 14}, {0x455a14ed, 20},
	{0xa9e3e905, 5}, {0xfcefa3f8, 9}, {0x676f02d9, 14}, {0x8d2a4c8a, 20},
	{0xfffa3942, 4}, {0x8771f681, 11}, {0x6d9d6122, 16}, {0xfde5380c, 23},
	{0xa4beea44, 4}, {0x4bdecfa9, 11}, {0xf6bb4b60, 16}, {0xbebfbc70, 23},
	{0x289b7ec6, 4}, {0xeaa127fa, 11}, {0xd4ef3085, 16}, {0x04881d05, 23},
	{0xd9d4d039, 4}, {0xe6db99e5, 11}, {0x1fa27cf8, 16}, {0xc4ac5665, 23},
	{0xf4292244, 6}, {0x432aff97, 10}, {0xab9423a7, 15}, {0xfc93a039, 21},
	{0x655b59c3, 6}, {0x8f0ccc92, 10}, {0xffeff47d, 15}, {0x85845dd1, 21},
	{0x6fa87e4f, 6}, {0xfe2ce6e0, 10}, {0xa3014314, 15}, {0x4e0811a1, 21},
	{0xf7537e82, 6}, {0xbd3af235, 10}, {0x2ad7d2bb, 15}, {0xeb86d391, 21}
};

t_dispatch_2		g_fg[4] =
{
	{md5_f0, 1, 0}, {md5_f1, 5, 1}, {md5_f2, 3, 5}, {md5_f3, 7, 0}
};

void	md5_process(t_info *info, uint32_t *w, uint32_t chunk_num)
{
	uint32_t	i;
	uint32_t	f;

	while (chunk_num--)
	{
		if (info->flag['d'])
			print_data_32(w, 16);
		i = -1;
		while (++i < 4)
			info->h_32[i] = info->ans_32[i];
		i = -1;
		while (++i < 64)
		{
			f = g_fg[(i >> 4)].f(info->h_32) + info->h_32[0] + g_d[i].k + \
				w[((g_fg[(i >> 4)].g_mul * i + g_fg[(i >> 4)].g_add) & 15)];
			info->h_32[0] = info->h_32[3];
			info->h_32[3] = info->h_32[2];
			info->h_32[2] = info->h_32[1];
			info->h_32[1] += ((f << g_d[i].lr) | (f >> (32 - g_d[i].lr)));
		}
		i = -1;
		while (++i < 4)
			info->ans_32[i] += info->h_32[i];
		w += 16;
	}
}

void	append_message(t_info *info, uint32_t *w, int len)
{
	int		j;

	if (info->flag['p'] && info->fd == 0 && !info->flag['s'])
		write(1, info->chunk, len);
	j = len >> 2;
	if (len & 3)
		w[j] = (w[j] & ((1 << ((len & 3) << 3)) - 1)) + \
				(0x80 << ((len & 3) << 3));
	else
		w[j] = 0x80;
	while ((++j & 15) != 14)
		w[j] = 0x00000000;
	w[j++] = ((info->total_len << 3) & 0xffffffff);
	w[j++] = (info->total_len >> 29);
	md5_process(info, w, (len >> 6) + (((len & 63) >= 56) ? 2 : 1));
}

void	md5_hash_string(t_info *info, char *s)
{
	uint32_t	i;
	uint64_t	j;
	uint64_t	len;

	init_32(info);
	len = ft_strlen(s);
	info->total_len = len;
	if (len >> 6)
	{
		md5_process(info, (uint32_t *)s, (len >> 6));
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
	append_message(info, (uint32_t *)(info->chunk), len);
	print_result(info, s);
}

int		hand_stdin(t_info *info, int tmp_len)
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

void	md5_hash_file(t_info *info, char *path)
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
			md5_process(info, (uint32_t *)(info->chunk), (tmp_len >> 6));
			tmp_len = (tmp_len == CHUNK_SIZE) ? 0 : hand_stdin(info, tmp_len);
		}
		else
			info->tmp += len;
	}
	append_message(info, (uint32_t *)(info->chunk), tmp_len);
	print_result(info, path);
}
