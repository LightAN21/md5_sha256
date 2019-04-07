/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 03:33:17 by jtsai             #+#    #+#             */
/*   Updated: 2018/07/13 13:54:26 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	char	*a;
	char	*b;

	a = (char *)s1;
	b = (char *)s2;
	while (*a != '\0' && *b != '\0')
	{
		if (*a != *b)
			return ((unsigned char)*a - (unsigned char)*b);
		a++;
		b++;
	}
	if (*a != *b)
		return ((unsigned char)*a - (unsigned char)*b);
	return (0);
}
