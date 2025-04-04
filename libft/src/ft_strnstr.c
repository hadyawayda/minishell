/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:45:42 by nabbas            #+#    #+#             */
/*   Updated: 2024/06/28 10:21:02 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	j;

	if (!*needle)
		return ((char *)haystack);
	while (*haystack && n > 0)
	{
		j = 0;
		while (*(haystack + j) == *(needle + j) && *(needle + j) && j < n)
		{
			j++;
		}
		if (!*(needle + j))
			return ((char *)haystack);
		haystack++;
		n--;
	}
	return (NULL);
}
