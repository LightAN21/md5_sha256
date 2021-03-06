/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 07:33:23 by jtsai             #+#    #+#             */
/*   Updated: 2019/03/12 13:18:08 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	g_32_k[64] =
{
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

uint32_t	rrotate_32(uint32_t n, int r)
{
	return ((n >> r) + (n << (32 - r)));
}

void		sha256_process_0(uint32_t *word, uint32_t w[])
{
	int	i;

	i = -1;
	while (++i < 16)
	{
		w[i] = ((word[i] & 0xff) << 24) + ((word[i] & 0xff00) << 8) +\
			((word[i] & 0xff0000) >> 8) + ((word[i] & 0xff000000) >> 24);
	}
	i = 15;
	while (++i < 64)
	{
		w[i] = w[i - 16] + w[i - 7] + \
			(rrotate_32(w[i - 15], 7) ^ rrotate_32(w[i - 15], 18) ^\
			(w[i - 15] >> 3)) +\
			(rrotate_32(w[i - 2], 17) ^ rrotate_32(w[i - 2], 19) ^\
			(w[i - 2] >> 10));
	}
}

void		sha256_process_1(uint32_t *h, uint32_t w[])
{
	int	i;
	int	tmp1;
	int tmp2;

	i = -1;
	while (++i < 64)
	{
		tmp1 = h[7] + g_32_k[i] + w[i] +\
			((h[4] & h[5]) ^ ((~h[4]) & h[6])) + ((rrotate_32(h[4], 6)) ^\
			(rrotate_32(h[4], 11)) ^ (rrotate_32(h[4], 25)));
		tmp2 = ((h[0] & h[1]) ^ (h[0] & h[2]) ^ (h[1] & h[2])) +\
			((rrotate_32(h[0], 2)) ^\
			(rrotate_32(h[0], 13)) ^ (rrotate_32(h[0], 22)));
		h[7] = h[6];
		h[6] = h[5];
		h[5] = h[4];
		h[4] = h[3] + tmp1;
		h[3] = h[2];
		h[2] = h[1];
		h[1] = h[0];
		h[0] = tmp1 + tmp2;
	}
}

void		sha256_process(t_info *info, uint32_t *words, uint32_t chunk_num)
{
	uint32_t	w[64];
	uint32_t	i;

	while (chunk_num--)
	{
		sha256_process_0(words, w);
		if (info->flag['d'])
			print_data_32(w, 16);
		i = -1;
		while (++i < 8)
			info->h_32[i] = info->ans_32[i];
		sha256_process_1(info->h_32, w);
		i = -1;
		while (++i < 8)
			info->ans_32[i] += info->h_32[i];
		words += 16;
	}
}
