/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 09:19:12 by nabbas            #+#    #+#             */
/*   Updated: 2024/06/28 10:15:33 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h" 

char	*ft_strcpy(char *dest, const char *src)
{
	char	*tmp;

	tmp = dest;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (tmp);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*duplicate;

	len = ft_strlen(s) + 1;
	duplicate = (char *)malloc(len * sizeof(char));
	if (duplicate == NULL)
	{
		return (NULL);
	}
	ft_strcpy(duplicate, s);
	return (duplicate);
}
