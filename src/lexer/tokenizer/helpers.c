/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:25:45 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/18 19:25:53 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

void	skip_whitespace(const char *input, int *i)
{
	while (ft_isspace(input[*i]))
		(*i)++;
}
