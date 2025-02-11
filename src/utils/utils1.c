/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 01:17:49 by fel-ghaz          #+#    #+#             */
/*   Updated: 2025/02/11 15:55:09 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_strcopy(char *dest, char *src)
{
	if (dest == NULL || src == NULL)
		return ;
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
}
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