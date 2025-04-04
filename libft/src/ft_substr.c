/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:26:19 by fel-ghaz          #+#    #+#             */
/*   Updated: 2025/04/04 19:45:09 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		j;
	char		*substr;

	i = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start > i)
		len = 0;
	else if (len > i - start)
		len = i - start;
	substr = (char *) malloc ((sizeof(char) * (len + 1)));
	if (!substr)
		return (NULL);
	j = 0;
	while (j < len)
	{
		substr[j] = s[start];
		j++;
		start++;
	}
	substr[j] = '\0';
	return (substr);
}
