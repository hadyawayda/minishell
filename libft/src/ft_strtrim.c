/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:50:39 by nabbas            #+#    #+#             */
/*   Updated: 2024/06/28 10:20:55 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	ft_char_in_set(char c, char const *set)
	{
	size_t	i;

	i = 0;
	while (set[i] != '\0' )
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	s;
	size_t	end;

	s = 0;
	while (ft_char_in_set(s1[s], set) && s1[s] != '\0')
		s++;
	end = ft_strlen(s1);
	while (ft_char_in_set(s1[end - 1], set) && end > s)
		end--;
	str = (char *)malloc(sizeof(char) * (end - s + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s < end)
		str[i++] = s1[s++];
	str[i] = 0 ;
	return (str);
}
