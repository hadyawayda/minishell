/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:11:56 by nabbas            #+#    #+#             */
/*   Updated: 2024/06/26 20:48:30 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substr;

	if (start >= (unsigned int)ft_strlen(s))
	{
		substr = malloc(1);
		if (!substr)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	if (ft_strlen(s) - start < len)
		substr = (char *) malloc(sizeof(*s) * ((ft_strlen(s) - start) + 1));
	else
		substr = (char *) malloc(sizeof(*s) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (s[start + i] != '\0' && len--)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
