/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_md5_fun.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 02:08:20 by dromansk          #+#    #+#             */
/*   Updated: 2019/04/24 18:36:02 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_MD5_FUN_H
# define SSL_MD5_FUN_H
# include "ssl_md5_structs.h"

unsigned			flip_end(unsigned n);
unsigned long		flip_end_512(unsigned long n);

int					get_input(int fd, int flags, char *input, char **file);
t_ssl_input			*make_input(int ac);

void				flag_error(char *name, char *flag, int dis);
void				error_nodis(char *input);

void				ssl_flags(char **av, t_ssl_input *input, int dis, int j);
void				cipher_flags(char **av, t_ssl_input *input, int dis, int j);
int					flag_val(char *flags, int dis, char *fun);
int					cipher_flag_val(char *flags, int dis, char *fun);

int					stdin_check(void);
void				bad_input(char *input);

int					handle_string(char **av, int j, t_ssl_input *input, int dis);
void				do_ssl(t_ssl_input *input2, char *input, int dis);

/*
** md5
*/

int					ft_md5(t_ssl_input *input);
void				hashing_functions_md5(t_md5_words *words, int i,
		unsigned *chunks);
uint32_t			left_rotate(uint32_t bits, uint32_t rot);
unsigned			flip_end(unsigned unflipped);
int					lessthan16(t_md5_words *words, int i);
int					lessthan32(t_md5_words *words, int i);
int					lessthan48(t_md5_words *words, int i);
int					upto64(t_md5_words *words, int i);

/*
** sha256 and sha224
*/

int					ft_sha256(t_ssl_input *input);
int					ft_sha224(t_ssl_input *input);
uint32_t			rightrotate(uint32_t input, uint32_t amount);
void				sha_process_chunk(char *chunk, t_sha_words *words);
int					sha_pad(char *input, unsigned len, t_sha_words *words);

/*
** sha512 and sha384
*/

int					ft_sha512(t_ssl_input *input);
int					ft_sha384(t_ssl_input *input);
void				process_chunk_512(char *chunk, t_512_words *words);
int					sha_pad_512(char *input, unsigned len, t_512_words *words);

/*
** base64
*/

int					ft_base64(t_ssl_input *input);
int					ft_base64_e(char *input, size_t len);
int					ft_base64_d(char *input, size_t len);
unsigned char		*expand_base(unsigned chunk);
unsigned char		*contract_base(unsigned chunk);
void				decrypt_chunk(unsigned char *d, int i, int p);
int					minus_pad(char *input);

/*
** des
*/

int					ft_des_cbc(t_ssl_input *input);
int					ft_des_ecb(t_ssl_input *input);
const unsigned long	*gen_key(unsigned long key);

#endif
