/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha512.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:39:49 by dromansk          #+#    #+#             */
/*   Updated: 2019/04/24 18:22:31 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_md5_enums.h"

void	print_sha512(void *w)
{
	t_512_words *words;

	words = (t_512_words *)w;
	ft_printf("%016lx%016lx%016lx%016lx%016lx%016lx%016lx%016lx", words->h0,
			words->h1, words->h2, words->h3, words->h4, words->h5, words->h6,
			words->h7);
	free(w);
}

void	split_padded_1024(char *fixed, int len, t_512_words *words)
{
	char			*chunk;
	int				i;

	i = 0;
	while (i < len)
	{
		chunk = ft_strnew(128);
		ft_memcpy(chunk, fixed + i, 128);
		process_chunk_512(chunk, words);
		free(chunk);
		i += 128;
	}
}

char	*flip_512(unsigned long *padded, int len)
{
	int				j;

	j = -1;
	while (++j < ((len) / 4))
		padded[j] = flip_end_512(padded[j]);
	return ((char *)padded);
}

/*int		sha_pad_512(char *input, unsigned len, t_512_words *words)
{
	int				i;
	unsigned long	flen;
	char			*padded;

	i = 1;
	while ((len + i + 8) % 128)
		i++;
	if (!(padded = ft_strnew(i + len + 8)))
		return (-1);
	padded = ft_memcpy(padded, input, len);
	padded[len] = (unsigned char)128;
	flen = (len * 8);
	padded = flip_512((unsigned long *)padded, len + i);
	ft_memcpy(padded + len + i, &flen, 8);
	split_padded_1024(padded, len + i + 8, words);
	return (0);
}*/

//if I'm completely wrong about how openssl pads 512
//then I can ditch this whole thing and just keep a pad section
void	sha_512_pad(t_ssl_input *input, void *words)
{
	static size_t	flen1;
	static size_t	flen2;
	t_512_words		*w;

	if (flen1 + (8 * input->read) < flen1)
		flen2 += 8;
	flen1 += (8 * input->read);
	if (input->read < BUFF_SIZE)
	{
		w = (t_512_words *)words;
		if (input->read + 1 > BUFF_SIZE - 16)
		{
			flip_512((unsigned long *)input->input, 128);
			split_padded_1024(input->input, 128, w);
			input->read -= 128;
			ft_memcpy(input->input, input->input + 128, input->read);
		}
		input->input[input->read++] = (unsigned char)128;
		while ((input->read + 16) % 128)
			input->input[input->read++] = 0;
//		flen = input->len2;
		ft_memcpy(input->input + input->read, &flen2, 8);
//		flen = input->len1;
		ft_memcpy(input->input + input->read + 8, &flen1, 8);
		input->read += 16;
	}
	flip_512((unsigned long *)input->input, input->read);//if the length field isn't supposed to be flipped then I'll have to copy len1 before len2 and put this line back at the top
}

void	*ft_sha512(t_ssl_input *input)
{
	t_512_words		*words;

	words = (t_512_words *)malloc(sizeof(t_512_words));
	words->h0 = 0x6a09e667f3bcc908;
	words->h1 = 0xbb67ae8584caa73b;
	words->h2 = 0x3c6ef372fe94f82b;
	words->h3 = 0xa54ff53a5f1d36f1;
	words->h4 = 0x510e527fade682d1;
	words->h5 = 0x9b05688c2b3e6c1f;
	words->h6 = 0x1f83d9abfb41bd6b;
	words->h7 = 0x5be0cd19137e2179;
	while (read_hash(input, words, &sha_512_pad) > 0)
		split_padded_1024(input->input, input->read, words);
/*	if (sha_pad_512(input->input, (unsigned)(input->len), words) < 0)
	{
		free(words);
		return (-1);
	}*/
//	print_sha512(words);
	if (input->read == -1)
	{
		free(words);
		words = NULL;
	}
	return (NULL);
}

/*
 * refer to sha256 for reading changes
*/
