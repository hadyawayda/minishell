/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 23:06:58 by hawayda           #+#    #+#             */
/*   Updated: 2025/04/04 20:47:36 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
	char *token;

	token = ft_strtok_r(str, delim, &str);
	return (token);
}
