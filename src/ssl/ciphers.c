/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ciphers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 20:35:00 by dromansk          #+#    #+#             */
/*   Updated: 2019/04/26 14:56:13 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_md5_enums.h"

/*
** write flag getting function for ciphers
** ciphers default to encryption
*/

t_ssl_input	*make_input(int ac)
{
	t_ssl_input	*input;

	if (!(input = (t_ssl_input *)malloc(sizeof(t_ssl_input))))
		return (NULL);
	input->args = ac;
	input->input = NULL;
	input->len = 0;
	input->flags = 0;
	input->infd = 0;
	input->outfd = 1;
	input->iv = 0;
	input->key = 0;
	input->pass = NULL;
	input->salt = 0;
	return (input);
}