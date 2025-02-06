/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-ghaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:14:37 by fel-ghaz          #+#    #+#             */
/*   Updated: 2024/06/11 11:08:37 by fel-ghaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*a;
	size_t				i;
	unsigned char		b;

	i = 0;
	a = (const unsigned char *)s;
	b = (unsigned char )c;
	while (i < n)
	{
		if (a[i] == b)
			return ((void *)(a + i));
		i++;
	}
	return (NULL);
}
