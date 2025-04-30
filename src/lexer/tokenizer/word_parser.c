/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 02:56:06 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/22 04:22:03 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

void	word_parser(const char *input, int *i, char **current_token)
{
	char	*temp;

	while (input[*i] && !ft_isdelimiter(input[*i])
		&& !is_operator_char(input[*i]) && input[*i] != '\''
		&& input[*i] != '"')
	{
		if (input[*i] == '$' && input[*i + 1] && (ft_isalnum(input[*i + 1])))
		{
			if (input[*i + 1] && (ft_isalnum(input[*i + 1]) || input[*i
					+ 1] == '_'))
				handle_expansion(input, i, current_token);
		}
		else
		{
			temp = append_char(*current_token, input[*i]);
			free(*current_token);
			*current_token = temp;
			(*i)++;
		}
	}
}
