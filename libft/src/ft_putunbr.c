/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 01:39:59 by hawayda           #+#    #+#             */
/*   Updated: 2025/04/04 19:45:09 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putunbr(unsigned int nb)
{
	int	length;

	length = 0;
	if (nb >= 10)
		length += ft_putunbr(nb / 10);
	ft_putchar((nb % 10) + '0');
	length += 1;
	return (length);
}
