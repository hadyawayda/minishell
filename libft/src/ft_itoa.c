/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:35:30 by nabbas            #+#    #+#             */
/*   Updated: 2024/06/26 21:55:23 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_sizeofchar(unsigned int n)
{
	unsigned int	size;

	size = 0;
	if (n == 0)
		size = 1;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	unsigned int	isntpos;
	unsigned int	len;
	unsigned int	npos;
	char			*result;

	isntpos = 0;
	if (n < 0)
		isntpos = 1;
	npos = -1 * n * (n < 0) + n * (n >= 0);
	len = ft_sizeofchar(npos) + isntpos;
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	result[len--] = '\0';
	while (npos > 9)
	{
		result[len--] = npos % 10 + '0';
		npos = npos / 10;
	}
	result[len--] = npos % 10 + '0';
	if (isntpos)
		result[0] = '-';
	return (result);
}
