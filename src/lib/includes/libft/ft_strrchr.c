/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-ghaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 07:25:33 by fel-ghaz          #+#    #+#             */
/*   Updated: 2024/06/14 07:25:37 by fel-ghaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	nc;
	size_t			i;
	size_t			last_pos;

	i = 0;
	last_pos = (size_t) - 1;
	nc = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == nc)
		{
			last_pos = i;
		}
		i++;
	}
	if (nc == '\0')
	{
		return ((char *)&s[i]);
	}
	else if (last_pos == (size_t) - 1)
	{
		return (NULL);
	}
	return ((char *)&s[last_pos]);
}
