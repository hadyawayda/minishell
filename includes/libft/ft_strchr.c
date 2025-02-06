/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-ghaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 07:25:04 by fel-ghaz          #+#    #+#             */
/*   Updated: 2024/06/14 07:25:10 by fel-ghaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	nc;
	size_t			i;

	i = 0;
	nc = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == nc)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (nc == '\0')
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}
