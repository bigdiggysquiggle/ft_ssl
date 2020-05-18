/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 02:29:52 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/22 17:00:35 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_md5_enums.h"

/*
** will need to verify if this works with binary files
*/

void			print_md5(void *w)
{
	t_md5_words *words;

	words = (t_md5_words*)w;
	words->a0 = flip_end(words->a0);
	words->b0 = flip_end(words->b0);
	words->c0 = flip_end(words->c0);
	words->d0 = flip_end(words->d0);
	ft_printf("%08x%08x%08x%08x", words->a0, words->b0, words->c0, words->d0);
	free(w);
}

void			split_input_32(char *chunk, t_md5_words *word)
{
	unsigned		chunks[16];
	int				i;
	int				j;
	int				num;

	i = 0;
	j = 0;
	while (j < 64)
	{
		ft_memcpy(&num, chunk + j, 4);
		chunks[i++] = num;
		j += 4;
	}
	i = -1;
	word->a = word->a0;
	word->b = word->b0;
	word->c = word->c0;
	word->d = word->d0;
	while (++i < 64)
		hashing_functions_md5(word, i, chunks);
	word->a0 += word->a;
	word->b0 += word->b;
	word->c0 += word->c;
	word->d0 += word->d;
	ft_bzero(chunks, 16 * sizeof(unsigned));
}

void			split_input_512(char *input, int len, t_md5_words *word)
{
	char			process[64];
	int				i;
	int				j;

	j = 0;
	while (j < len)
	{
		i = 0;
		while (i < 64)
			process[i++] = input[j++];
		split_input_32(process, word);
	}
	ft_bzero(process, 64);
}

void	md5_pad(t_ssl_input *input, void *words)
{
	size_t		pad;
	size_t		flen;
	t_md5_words	*w;

	if (input->read < BUFF_SIZE)
	{
		w = (t_md5_words *)words;
		if (input->read + 1 > BUFF_SIZE - 8)
		{
			split_input_512(input->input, 64, w);
			input->read -= 64;
			ft_memcpy(input->input, input->input + 64, input->read);
		}
		pad = (size_t)(input->read + 1);
		while ((pad + 8) % 64)
			input->input[pad++] = 0;
		input->input[input->read] = (unsigned char)128;
		flen = input->len * 8;
		ft_memcpy(input->input + pad, &flen, 8); //this may be incorrect so I'm leaving the old adaption below
		input->read = pad + 8;
	}
}

void		*ft_md5(t_ssl_input *input)
{
//	int				flen;
//	size_t			i;
//	char			*fixed;
	t_md5_words		*words;

	words = (t_md5_words *)malloc(sizeof(t_md5_words));
	words->a0 = 0x67452301;
	words->b0 = 0xefcdab89;
	words->c0 = 0x98badcfe;
	words->d0 = 0x10325476;
/*	i = 1 + input->len;
	while ((i + 8) % 64)
		i++;
	if (!(fixed = ft_strnew(i + 8)))
		return (-1);
	fixed = ft_memcpy(fixed, input->input, input->len);
	fixed[input->len] = (unsigned char)128;
	flen = (int)(input->len * 8);
	ft_memcpy(fixed + i, &flen, 4);
	consider testing stdin here*/
	while (read_hash(input, words, &md5_pad) > 0)
		split_input_512(input->input, input->read, words);
//	if (input->read != -1)
//		print_md5(words);
	ft_bzero(input->input, BUFF_SIZE);
	if (input->read == -1)
	{
		free(words);
		words = NULL;
	}
//	free(fixed);
	return (words);
}

/*
 * read up to BUFF_SIZE and drop them chunks through md5
 * as soon as a read is less than BUFF_SIZE do the padding
 * - make sure there's consistently enough room to pad
 *   - maybe make the padding be a string?
 *   - or run a few chunks through to make sure there's room
 * then run those chunks through the algo as usual
*/
