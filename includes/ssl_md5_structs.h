/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_md5_structs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 02:04:59 by dromansk          #+#    #+#             */
/*   Updated: 2019/05/09 17:10:33 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_MD5_STRUCTS_H
# define SSL_MD5_STRUCTS_H
# define MIN_BUFF 384
# define BUFF_MULT 4000
# define BUFF_SIZE MIN_BUFF * BUFF_MULT

/*
** MIN_BUFF is a multiple of each minimum block size for 
** each hash and cipher. BUFF_MULT is an arbitrary number
** to create a sizeable buffer that's smaller than INT_MAX
** when used for all hashes and ciphers including the
** expansion and contraction of base64
*/

typedef struct s_md5_words	t_md5_words;
typedef struct s_sha_words	t_sha_words;
typedef struct s_512_words	t_512_words;
typedef struct s_ssl_input	t_ssl_input;

struct	s_md5_words
{
	unsigned		f;
	unsigned		a;
	unsigned		b;
	unsigned		c;
	unsigned		d;
	unsigned		a0;
	unsigned		b0;
	unsigned		c0;
	unsigned		d0;
};

struct	s_sha_words
{
	unsigned		r;
	unsigned		a;
	unsigned		b;
	unsigned		c;
	unsigned		d;
	unsigned		e;
	unsigned		f;
	unsigned		g;
	unsigned		h;
	unsigned		h0;
	unsigned		h1;
	unsigned		h2;
	unsigned		h3;
	unsigned		h4;
	unsigned		h5;
	unsigned		h6;
	unsigned		h7;
	unsigned		tmp1;
	unsigned		tmp2;
	unsigned		tmp3;
	unsigned		tmp4;
	unsigned		tmp5;
	unsigned		tmp6;
};

struct	s_512_words
{
	unsigned long	r;
	unsigned long	a;
	unsigned long	b;
	unsigned long	c;
	unsigned long	d;
	unsigned long	e;
	unsigned long	f;
	unsigned long	g;
	unsigned long	h;
	unsigned long	h0;
	unsigned long	h1;
	unsigned long	h2;
	unsigned long	h3;
	unsigned long	h4;
	unsigned long	h5;
	unsigned long	h6;
	unsigned long	h7;
	unsigned long	tmp1;
	unsigned long	tmp2;
	unsigned long	tmp3;
	unsigned long	tmp4;
	unsigned long	tmp5;
	unsigned long	tmp6;
};

struct	s_ssl_input
{
	int				args;
	char			input[BUFF_SIZE];
	char			base[BUFF_SIZE / 3 * 4];
	int				read;
	size_t			len;
	size_t			len2;
	int				flags;
	int				curr_flag;
	int				infd;
	int				outfd;
	unsigned long	key;
	unsigned long	iv;
	unsigned long	salt;
	char			*pass;
	char			*sflag;
	char			*sstring;
};

#endif
