/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:24:18 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/22 03:52:20 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

int	quote_parser(const char *input, int *i, char **current_token)
{
	char	quote_char;
	char	*temp;

	quote_char = input[*i];
	if (quote_char == '"' && *i > 0 && input[*i - 1] == '$')
	{
			(*i) -= 1;
			*current_token = ft_strdup("");

			*i += 2;  
			while (input[*i] && input[*i] != '"')
			{
					char *tmp = append_char(*current_token, input[*i]);
					free(*current_token);
					*current_token = tmp;
					(*i)++;
			}
			if (input[*i] == '"')
					(*i)++;
			return 0;
	}

	(*i)++;
	while (input[*i])
	{
		if (input[*i] == quote_char)
		{
			(*i)++;
			return (0);
		}
		if (quote_char == '"' && input[*i] == '$')
			handle_expansion(input, i, current_token);
		else
		{
			temp = append_char(*current_token, input[*i]);
			free(*current_token);
			*current_token = temp;
			(*i)++;
		}
	}
	ft_printf("Unclosed quote detected\n");
	return (-1);
}
