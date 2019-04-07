/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 07:45:53 by jtsai             #+#    #+#             */
/*   Updated: 2019/03/12 12:09:42 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	g_init_32[3][8] =
{
	{0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0, 0, 0, 0},
	{
		0xc1059ed8, 0x367cd507, 0x3070dd17, 0xf70e5939,
		0xffc00b31, 0x68581511, 0x64f98fa7, 0xbefa4fa4
	},
	{
		0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
		0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
	}
};

uint64_t	g_init_64[2][8] =
{
	{
		0xcbbb9d5dc1059ed8, 0x629a292a367cd507,
		0x9159015a3070dd17, 0x152fecd8f70e5939,
		0x67332667ffc00b31, 0x8eb44a8768581511,
		0xdb0c2e0d64f98fa7, 0x47b5481dbefa4fa4
	},
	{
		0x6a09e667f3bcc908, 0xbb67ae8584caa73b,
		0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1,
		0x510e527fade682d1, 0x9b05688c2b3e6c1f,
		0x1f83d9abfb41bd6b, 0x5be0cd19137e2179
	}
};

void		init_32(t_info *info)
{
	int			i;
	int			type;

	type = (info->hash_type >> 7);
	i = -1;
	while (++i < 8)
		info->ans_32[i] = g_init_32[type][i];
	info->tmp = info->chunk;
	info->total_len = 0;
}

void		init_64(t_info *info)
{
	int			i;
	int			type;

	type = (info->hash_type >> 9);
	i = -1;
	while (++i < 8)
		info->ans_64[i] = g_init_64[type][i];
	info->tmp = info->chunk;
	info->total_len = 0;
}
