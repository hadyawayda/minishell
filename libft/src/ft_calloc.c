/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 08:56:16 by nabbas            #+#    #+#             */
/*   Updated: 2024/06/28 10:23:02 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"  

static void	s_zero(void *s, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n-- > 0)
		*p++ = 0;
}

void	*ft_calloc(size_t count, size_t n)
{
	void	*mem;

	if (count > 0 && n > 0 && count > (UINT_MAX / n))
		return (NULL);
	mem = malloc(count * n);
	if (!mem)
		return (NULL);
	s_zero(mem, count * n);
	return (mem);
}
