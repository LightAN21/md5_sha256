/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 12:54:04 by jtsai             #+#    #+#             */
/*   Updated: 2019/03/12 12:57:06 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	is_directory(int type, char *s)
{
	ft_printf("ft_ssl: ");
	if (type == 5)
		ft_printf("md5: %s: Is a directory\n", s);
	else
		ft_printf("sha%d: %s: Is a directory\n", type, s);
	return (1);
}
