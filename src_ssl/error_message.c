/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 15:27:04 by jtsai             #+#    #+#             */
/*   Updated: 2019/03/12 14:53:46 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	usage(void)
{
	ft_printf("usage: ./ft_ssl command [-dpqr] [-s string] [file ...]\n");
	ft_printf("\nStandard commands:\n");
	ft_printf("md5\nsha224\nsha256\nsha384\nsha512\n\n");
	return (0);
}

int	invalid_command(char *s)
{
	ft_printf("ft_ssl: Error: \'%s\' is an invalid command.\n", s);
	return (usage());
}

int	illegal_option(int type, char c)
{
	ft_printf("ft_ssl: ");
	if (type == 5)
		ft_printf("md5: ");
	else
		ft_printf("sha%d: ", type);
	ft_printf("illegal option -- %c\n", c);
	return (usage());
}

int	file_not_found(int type, char *s)
{
	ft_printf("ft_ssl: ");
	if (type == 5)
		ft_printf("md5: %s: No such file or directory\n", s);
	else
		ft_printf("sha%d: %s: No such file or directory\n", type, s);
	return (1);
}

int	string_missing(void)
{
	ft_printf("ft_ssl: option requires an argument -- s\n");
	ft_printf("usage: command [-pqr] [-s string] [file ...]\n");
	return (0);
}
