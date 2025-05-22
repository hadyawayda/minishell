/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 23:06:58 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/22 21:39:55 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok_r(char *str, const char *delim, char **next)
{
	char	*token;

	token = ft_strnstr(str, delim, ft_strlen(str));
	if (token)
	{
		*token = '\0';
		*next = token + ft_strlen(delim);
	}
	else
	{
		*next = NULL;
	}
	return (token);
}

char	*ft_strtok(char *str, const char *delim)
{
	char	*token;

	token = ft_strtok_r(str, delim, &str);
	return (token);
}
