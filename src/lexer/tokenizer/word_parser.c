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

// void	word_parser(const char *input, int *i, char **current_token)
// {
// 	char	*temp;

// 	while (input[*i] && !ft_isdelimiter(input[*i])
// 		&& !is_operator_char(input[*i]) && input[*i] != '\''
// 		&& input[*i] != '"')
// 	{
// 		if (input[*i] == '$' && input[*i + 1] && (ft_isalnum(input[*i + 1])))
// 			handle_expansion(input, i, current_token);
// 		else
// 		{
// 			while (input[*i] && !ft_isdelimiter(input[*i])
// 				&& !is_operator_char(input[*i]) && input[*i] != '\''
// 				&& input[*i] != '"')
// 			{
// 				// If we see '$'
// 				if (input[*i] == '$')
// 				{
// 					// Check for valid var name
// 					if (input[*i + 1] && (ft_isalnum(input[*i + 1]) || input[*i
// 							+ 1] == '_'))
// 					{
// 						// Perform the expansion
// 						handle_expansion(input, i, current_token);
// 					}
// 					else
// 					{
// 						// Treat '$' as literal
// 						temp = append_char(*current_token, '$');
// 						free(*current_token);
// 						*current_token = temp;
// 						(*i)++;
// 					}
// 				}
// 				else
// 				{
// 					// Normal character
// 					temp = append_char(*current_token, input[*i]);
// 					free(*current_token);
// 					*current_token = temp;
// 					(*i)++;
// 				}
// 			}
// 		}
// 	}
// }

// void	word_parser(const char *input, int *i, char **current_token)
// {
// 	while (input[*i] && !ft_isdelimiter(input[*i])
// 		&& !is_operator_char(input[*i]) && input[*i] != '\''
// 		&& input[*i] != '"')
// 	{
// 		if (input[*i] == '$')
// 			handle_expansion(input, i, current_token);
// 		else
// 		{
// 			ft_strjoin_char(*current_token, input[*i]);
// 			(*i)++;
// 		}
// 	}
// }
