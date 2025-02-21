/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:25:45 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/21 04:27:18 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

int	skip_whitespace(const char *input, int *i)
{
	int	skipped;

	skipped = 0;
	while (input[*i] == ' ' || input[*i] == '\t')
	{
		(*i)++;
		skipped = 1;
	}
	return (skipped);
}
