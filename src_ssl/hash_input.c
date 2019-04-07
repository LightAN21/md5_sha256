/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 10:25:47 by jtsai             #+#    #+#             */
/*   Updated: 2019/03/11 16:07:14 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	hash_string(t_info *info, char *s)
{
	int	type;

	type = info->hash_type;
	if (type == 5)
		md5_hash_string(info, s);
	else if (type == 224 || type == 256)
		sha256_hash_string(info, s);
	else if (type == 384 || type == 512)
		sha512_hash_string(info, s);
}

void	hash_file(t_info *info, char *path)
{
	int	type;

	type = info->hash_type;
	if (type == 5)
		md5_hash_file(info, path);
	else if (type == 224 || type == 256)
		sha256_hash_file(info, path);
	else if (type == 384 || type == 512)
		sha512_hash_file(info, path);
}

int		hash_stdin(t_info *info)
{
	int	type;

	type = info->hash_type;
	if (type == 5)
		md5_hash_file(info, 0);
	else if (type == 224 || type == 256)
		sha256_hash_file(info, 0);
	else if (type == 384 || type == 512)
		sha512_hash_file(info, 0);
	return (0);
}
