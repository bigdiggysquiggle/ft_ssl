/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlower.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 21:52:27 by dromansk          #+#    #+#             */
/*   Updated: 2019/03/29 16:26:16 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strlower(char *s)
{
	char	*n;
	int		i;

	n = s;
	i = -1;
	while (n[++i])
		n[i] = ft_tolower(n[i]);
	return (n);
}
