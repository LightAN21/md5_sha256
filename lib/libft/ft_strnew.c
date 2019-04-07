/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 10:41:56 by jtsai             #+#    #+#             */
/*   Updated: 2018/07/14 12:11:15 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*s;
	size_t	i;

	s = (char *)malloc((size + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	i = 0;
	while (i < size)
		s[i++] = '\0';
	s[i] = '\0';
	return (s);
}
