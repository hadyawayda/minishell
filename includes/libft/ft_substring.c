/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substring.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:40:07 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/22 21:40:09 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substring(const char *src, int start, int end)
{
	char	*dest;
	int		len;

	if (end <= start)
		return (ft_strdup(""));
	len = end - start;
	dest = malloc(len + 1);
	if (!dest)
		return (NULL);
	ft_strncpy(dest, src + start, len);
	dest[len] = '\0';
	return (dest);
}
