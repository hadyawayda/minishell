/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_only_whitespace.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:27:44 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/03 13:27:45 by hawayda          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "libft.h"

bool   ft_is_only_whitespace(char *s)
{
    int    i;

    i = 0;
    while (s[i] != '\0')
    {
        if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
            return false;
        i++;
    }
    return true;
}
