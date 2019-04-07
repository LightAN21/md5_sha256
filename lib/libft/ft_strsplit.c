/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 11:30:56 by jtsai             #+#    #+#             */
/*   Updated: 2018/08/12 16:47:49 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	int		num;
	int		i;
	int		k;
	int		len;
	char	**x;

	if (s == NULL)
		return (NULL);
	num = ft_words(s, c);
	if (!(x = (char **)malloc((num + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	k = -1;
	while (num--)
	{
		while (s[i] == c)
			i++;
		len = ft_letters(s, i, c);
		if (!(x[++k] = ft_strsub(s, (unsigned int)i, (size_t)len)))
			return (NULL);
		i += len;
	}
	x[++k] = NULL;
	return (x);
}
