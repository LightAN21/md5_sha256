/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 13:45:19 by jtsai             #+#    #+#             */
/*   Updated: 2019/03/12 10:45:18 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	print_data_32(uint32_t *w, int len)
{
	int i;

	i = -1;
	while (++i < len)
	{
		ft_printf("%#010x ", w[i]);
		if ((i & 3) == 3)
			ft_printf("\n");
	}
	ft_printf("\n");
}

void	print_data_64(uint64_t *w, int len)
{
	int i;

	i = -1;
	while (++i < len)
	{
		ft_printf("%#018llx ", w[i]);
		if ((i & 3) == 3)
			ft_printf("\n");
	}
	ft_printf("\n");
}

void	print_type(t_info *info, char *str)
{
	if (!info->flag['r'] && !info->flag['q'] &&
		(info->fd != 0 || info->flag['s']))
	{
		if (info->hash_type == 5)
			ft_printf("MD5 ");
		else
			ft_printf("SHA%d ", info->hash_type);
		if (str && !info->flag['s'])
			ft_printf("(%s) = ", str);
		else if (info->flag['s'])
			ft_printf("(\"%s\") = ", str);
	}
}

void	print_type_r(t_info *info, char *str)
{
	if (info->flag['r'] && !info->flag['q'])
	{
		if (str && !info->flag['s'])
			ft_printf(" %s", str);
		else if (info->flag['s'])
			ft_printf(" \"%s\"", str);
	}
	ft_printf("\n");
}

void	print_result(t_info *info, char *str)
{
	int	i;

	print_type(info, str);
	i = -1;
	if (info->hash_type == 5)
	{
		info->tmp = (char *)info->ans_32;
		while (++i < 16)
			ft_printf("%02x", (info->tmp[i] & 0xff));
	}
	else if (info->hash_type == 224 || info->hash_type == 256)
	{
		while (++i < 7)
			ft_printf("%08x", info->ans_32[i]);
		if (info->hash_type == 256)
			ft_printf("%08x", info->ans_32[7]);
	}
	else if (info->hash_type == 384 || info->hash_type == 512)
	{
		while (++i < 6)
			ft_printf("%016llx", info->ans_64[i]);
		if (info->hash_type == 512)
			ft_printf("%016llx%016llx", info->ans_64[6], info->ans_64[7]);
	}
	print_type_r(info, str);
}
