/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:55:57 by jtsai             #+#    #+#             */
/*   Updated: 2019/03/08 08:33:09 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPATCH_H
# define DISPATCH_H

typedef struct		s_dispatch
{
	uint32_t		k;
	uint32_t		lr;
}					t_dispatch;

typedef struct		s_dispatch_2
{
	uint32_t		(*f)(uint32_t t[]);
	uint32_t		g_mul;
	uint32_t		g_add;
}					t_dispatch_2;

uint32_t			md5_f0(uint32_t t[]);
uint32_t			md5_f1(uint32_t t[]);
uint32_t			md5_f2(uint32_t t[]);
uint32_t			md5_f3(uint32_t t[]);

#endif
