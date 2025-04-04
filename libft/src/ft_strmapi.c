/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:27:15 by nabbas            #+#    #+#             */
/*   Updated: 2024/06/26 22:31:40 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	size_t			len;
	char			*ns;

	i = 0;
	len = ft_strlen(s);
	ns = (char *) malloc(sizeof(char) * (len + 1));
	if (!ns)
		return (NULL);
	while (s[i] != '\0')
	{
		ns[i] = f (i, s[i]);
		i++;
	}
	ns[i] = '\0';
	return (ns);
}
