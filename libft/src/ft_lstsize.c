/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:58:15 by nabbas            #+#    #+#             */
/*   Updated: 2024/06/29 17:43:04 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0 ;
	while (lst != NULL)
	{
		count++;
		lst = lst -> next ;
	}
	return (count);
}
