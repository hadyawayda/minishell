/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:31:47 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/22 21:08:17 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type != (t_tokentype) -1)
	{
		printf("%s", tokens[i].value);
		if (tokens[i + 1].type != (t_tokentype) - 1)
			printf(" ");
		i++;
	}
	printf("\n");
}
