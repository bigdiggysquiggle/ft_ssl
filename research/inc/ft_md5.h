/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:43:42 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/08 10:37:12 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/time.h>

# include "ft_ssl_core.h"
# include "ft_ssl_helper_functions.h"

# define MD5_BUFFER_SIZE 64
# define MD5_TESTS 8

typedef	struct			s_md5_state
{
	uint32_t			state[4];
	unsigned char		buf[MD5_BUFFER_SIZE * 2];
	int					ret;
	uint64_t			length;
}						t_md5_state;

void					ft_md5(t_task *task);
void					md5_from_file(t_task *task, t_md5_state *state);
void					md5_from_string(t_task *task, t_md5_state *state);
void					md5_from_stdin(t_task *task, t_md5_state *state);
t_md5_state				*md5_init_state(void);
void					md5_update_state(t_md5_state *state);
t_md5_state				*md5_pad(t_md5_state *state);
void					md5_transform(t_md5_state *state);
void					get_f_and_g(uint32_t *f, uint32_t *g,
							uint32_t state_copy[4], uint32_t i);

/*
** Test suite
*/

void					md5_test_suite(void);
char					**md5_get_test_strings(void);
char					**md5_get_result_strings(void);

/*
** Helper functions
*/

uint32_t				md5_f(uint32_t x, uint32_t y, uint32_t z);
uint32_t				md5_g(uint32_t x, uint32_t y, uint32_t z);
uint32_t				md5_h(uint32_t x, uint32_t y, uint32_t z);
uint32_t				md5_i(uint32_t x, uint32_t y, uint32_t z);

void					decode(uint32_t *output, unsigned char *input,
							unsigned int len);

static const uint32_t	g_md5_t[64] = {
	0xd76aa478,
	0xe8c7b756,
	0x242070db,
	0xc1bdceee,
	0xf57c0faf,
	0x4787c62a,
	0xa8304613,
	0xfd469501,
	0x698098d8,
	0x8b44f7af,
	0xffff5bb1,
	0x895cd7be,
	0x6b901122,
	0xfd987193,
	0xa679438e,
	0x49b40821,
	0xf61e2562,
	0xc040b340,
	0x265e5a51,
	0xe9b6c7aa,
	0xd62f105d,
	0x2441453,
	0xd8a1e681,
	0xe7d3fbc8,
	0x21e1cde6,
	0xc33707d6,
	0xf4d50d87,
	0x455a14ed,
	0xa9e3e905,
	0xfcefa3f8,
	0x676f02d9,
	0x8d2a4c8a,
	0xfffa3942,
	0x8771f681,
	0x6d9d6122,
	0xfde5380c,
	0xa4beea44,
	0x4bdecfa9,
	0xf6bb4b60,
	0xbebfbc70,
	0x289b7ec6,
	0xeaa127fa,
	0xd4ef3085,
	0x4881d05,
	0xd9d4d039,
	0xe6db99e5,
	0x1fa27cf8,
	0xc4ac5665,
	0xf4292244,
	0x432aff97,
	0xab9423a7,
	0xfc93a039,
	0x655b59c3,
	0x8f0ccc92,
	0xffeff47d,
	0x85845dd1,
	0x6fa87e4f,
	0xfe2ce6e0,
	0xa3014314,
	0x4e0811a1,
	0xf7537e82,
	0xbd3af235,
	0x2ad7d2bb,
	0xeb86d391
};

static const uint32_t	g_md5_s[64] = {
	7, 12, 17, 22,
	7, 12, 17, 22,
	7, 12, 17, 22,
	7, 12, 17, 22,
	5, 9, 14, 20,
	5, 9, 14, 20,
	5, 9, 14, 20,
	5, 9, 14, 20,
	4, 11, 16, 23,
	4, 11, 16, 23,
	4, 11, 16, 23,
	4, 11, 16, 23,
	6, 10, 15, 21,
	6, 10, 15, 21,
	6, 10, 15, 21,
	6, 10, 15, 21
};

#endif
