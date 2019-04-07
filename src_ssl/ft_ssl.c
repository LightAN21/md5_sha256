/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 14:37:26 by jtsai             #+#    #+#             */
/*   Updated: 2019/03/12 14:48:55 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		check_hash_type(char *s)
{
	int type;

	if (ft_strcmp(s, "md5") == 0)
		return (5);
	else if (ft_strlen(s) == 6 && (s[0] == 's' && s[1] == 'h' && s[2] == 'a'))
	{
		type = ft_atoi(s + 3);
		if (type != 224 && type != 256 && type != 384 && type != 512)
			return (-1);
		return (type);
	}
	return (-1);
}

int		deal_flags(t_info *info, char *s)
{
	int i;

	i = 0;
	while (s[++i])
	{
		if ('q' <= s[i] && s[i] <= 's')
			info->flag[(int)s[i]] = 1;
		else if (info->flag['p'] == 0 && s[i] == 'p')
		{
			info->flag['p'] = 1;
			hash_stdin(info);
		}
		else if (s[i] == 'p')
			hash_string(info, "");
		else if (s[i] == 'd')
			info->flag['d'] = 1;
		else
			return (illegal_option(info->hash_type, s[i]));
	}
	return (1);
}

int		check_arguments(t_info *info, char *s)
{
	if (s[0] == '-' && !info->flag['s'] && !info->flag['f'])
	{
		if (!deal_flags(info, s))
			return (0);
	}
	else if (!info->flag['s'])
	{
		info->flag['f'] = 1;
		if (!stat(s, &st) && S_ISDIR(st.st_mode))
			return (is_directory(info->hash_type, s));
		if ((info->fd = open(s, O_RDONLY)) < 0)
			return (file_not_found(info->hash_type, s));
		hash_file(info, s);
		close(info->fd);
	}
	else if (info->flag['s'])
	{
		hash_string(info, s);
		info->flag['s'] = 0;
	}
	return (1);
}

int		only_stdin(t_info *info, int ac, char **av)
{
	int	i;
	int j;

	i = 1;
	while (++i < ac)
	{
		if (av[i][0] != '-')
			return (0);
		else
		{
			j = 0;
			while (av[i][++j])
			{
				if (av[i][j] == 'p')
					info->chunk[0] = 1;
				if (av[i][j] == 's' ||
					(av[i][j] != 'q' && av[i][j] != 'r' && av[i][j] != 'd'))
					return (0);
			}
		}
	}
	if (info->chunk[0])
		info->flag['p'] = 1;
	return (1);
}

int		main(int argc, char **argv)
{
	t_info	info;
	int		i;

	if (argc < 2)
		return (usage());
	ft_memset(&info, 0, sizeof(info) - sizeof(info.chunk));
	if ((info.hash_type = check_hash_type(argv[1])) == -1)
		return (invalid_command(argv[1]));
	if (argc >= 3 && ft_strlen(argv[2]) == 2 &&
		argv[2][0] == '-' && argv[2][1] == 'd')
		info.flag['d'] = 1;
	if (only_stdin(&info, argc, argv))
		return (hash_stdin(&info));
	i = 1;
	while (++i < argc)
	{
		if (!check_arguments(&info, argv[i]))
			return (0);
	}
	if (info.flag['s'] == 1)
		return (string_missing());
	return (0);
}
