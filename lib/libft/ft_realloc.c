/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:25:40 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/17 22:54:31 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new;
	size_t	old;
	size_t	i;

	if (ptr)
		old = ft_strlen(ptr);
	else
		old = 0;
	new = malloc(size);
	if (!new)
		return (NULL);
	i = 0;
	while (i < old)
	{
		((char *)new)[i] = ((char *)ptr)[i];
		i++;
	}
	free(ptr);
	return (new);
}
