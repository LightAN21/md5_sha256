/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 15:12:40 by jtsai             #+#    #+#             */
/*   Updated: 2019/03/12 12:53:40 by jtsai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H
# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include "dispatch.h"
# include <sys/types.h>
# include <sys/stat.h>
# define CHUNK_NUM 8192
# define CHUNK_SIZE (CHUNK_NUM << 7)

struct stat st;

typedef struct		s_info
{
	uint32_t		ans_32[8];
	uint64_t		ans_64[8];
	uint32_t		h_32[8];
	uint64_t		h_64[8];
	uint64_t		total_len;
	int				flag[128];
	int				hash_type;
	int				fd;
	char			*tmp;
	char			chunk[(CHUNK_SIZE << 1) + 128];
}					t_info;

int					usage(void);
int					invalid_command(char *s);
int					illegal_option(int type, char c);
int					file_not_found(int type, char *s);
int					string_missing(void);
int					is_directory(int type, char *s);

int					hash_stdin(t_info *info);
void				hash_file(t_info *info, char *path);
void				hash_string(t_info *info, char *s);

void				init_32(t_info *info);
void				init_64(t_info *info);
void				print_data_32(uint32_t *w, int len);
void				print_data_64(uint64_t *w, int len);
void				print_result(t_info *info, char *path);

void				md5_hash_string(t_info *info, char *s);
void				md5_hash_file(t_info *info, char *path);

void				sha256_hash_string(t_info *info, char *s);
void				sha256_hash_file(t_info *info, char *path);
void				sha256_process(t_info *info, uint32_t *words,
									uint32_t chunk_num);

void				sha512_hash_string(t_info *info, char *s);
void				sha512_hash_file(t_info *info, char *path);
void				sha512_process(t_info *info, uint64_t *words,
									uint64_t chunk_num);

uint64_t			reverse_word(uint64_t n);

#endif
