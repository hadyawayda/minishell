/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:52:35 by hawayda           #+#    #+#             */
/*   Updated: 2025/03/31 21:52:45 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strcat(char *dest, char *source)
{
	if (dest == NULL || source == NULL)
		return ;
	while (*dest)
		dest++;
	while (*source)
	{
		*dest = *source;
		dest++;
		source++;
	}
	*dest = '\0';
}
