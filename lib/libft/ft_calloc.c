/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-ghaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 07:27:04 by fel-ghaz          #+#    #+#             */
/*   Updated: 2024/06/14 07:27:09 by fel-ghaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	s_zero(void *s, size_t n)
{
	while (n--)
		*(unsigned char *)s++ = 0;
}

void	*ft_calloc(size_t nbr, size_t s)
{
	void	*ptr;

	if (nbr && s && nbr > (2147483648 / s))
		return (NULL);
	ptr = malloc(nbr * s);
	if (!ptr)
		return (NULL);
	else
		s_zero(ptr, nbr * s);
	return (ptr);
}
