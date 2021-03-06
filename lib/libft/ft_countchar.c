/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 22:30:24 by jtsai             #+#    #+#             */
/*   Updated: 2018/10/26 22:31:44 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countchar(char *s, char c)
{
	int	i;
	int	num;

	num = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			num++;
	}
	return (num);
}
