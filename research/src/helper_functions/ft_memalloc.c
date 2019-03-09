/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:08:33 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/26 12:37:33 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Using malloc, allocates memory of size size and returns a pointer to it.
** The allocated memory is initialized at 0.
*/

#include "ft_ssl_helper_functions.h"

void	*ft_memalloc(size_t size)
{
	void	*p;

	if (!(p = malloc(size)))
		return (NULL);
	return (ft_memset(p, 0, size));
}
