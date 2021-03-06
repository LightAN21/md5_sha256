/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 19:30:51 by jtsai             #+#    #+#             */
/*   Updated: 2018/07/28 20:02:37 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*x;

	x = (char *)s;
	while (*x)
	{
		if (*x == (char)c)
			return (x);
		x++;
	}
	if (*x == (char)c)
		return (x);
	return (NULL);
}
