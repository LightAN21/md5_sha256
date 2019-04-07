/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 10:19:32 by jtsai             #+#    #+#             */
/*   Updated: 2018/10/24 12:29:29 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		read_file(int fd, char **file, int n, int m)
{
	int		k;
	char	buff[BUFF_SIZE + 1];
	char	*t;

	while ((t = ft_strstr(file[fd] + n, "\n")) == NULL)
	{
		if ((k = read(fd, buff, BUFF_SIZE)) < 0)
			return (-2);
		else if ((k == 0 && file[fd] == NULL) ||
				(k == 0 && file[fd][0] == '\0'))
			return (-1);
		else if (k == 0)
			return (n + m);
		buff[k] = '\0';
		if (file[fd] == NULL)
			if (!(file[fd] = ft_strnew(1)))
				return (-2);
		if (!(t = ft_strjoin(file[fd], buff)))
			return (-2);
		free(file[fd]);
		file[fd] = t;
		n += m;
		m = k;
	}
	return ((int)(t - file[fd]) / sizeof(char));
}

int		get_next_line(const int fd, char **line)
{
	int			n;
	int			len;
	char		*t;
	static char	*file[777];

	if (fd < 0 || line == NULL)
		return (-1);
	n = read_file(fd, file, 0, 0);
	if (n < 0)
		return (n + 1);
	t = file[fd];
	len = ft_strlen(t);
	if (!(*line = ft_strsub(t, 0, (t[n] == '\n') ? n : len)))
		return (-1);
	if ((n > 0 && t[n] == '\n') || (t[0] == '\n' && len > 1))
		file[fd] = ft_strsub((char *)t, n + 1, len - n - 1);
	else
		file[fd] = ft_strnew(0);
	if (file[fd] == NULL)
		return (-1);
	free(t);
	return (1);
}
