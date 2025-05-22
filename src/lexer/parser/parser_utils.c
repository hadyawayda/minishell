/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:31:47 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/22 22:46:50 by hawayda          ###   ########.fr       */
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

// static const char *g_token_names[] = {
//     [T_WORD]          = "WORD",
//     [T_PIPE]          = "PIPE",
//     [T_AND]           = "AND",
//     [T_OR]            = "OR",
//     [T_REDIR_IN]      = "REDIR_IN",
//     [T_REDIR_OUT]     = "REDIR_OUT",
//     [T_REDIR_HERE]    = "HEREDOC",
//     [T_REDIR_APPEND]  = "APPEND",
//     [T_LPAREN]        = "LPAREN",
//     [T_RPAREN]        = "RPAREN",
// };

// void print_tokens(t_token *tokens)
// {
//     int i = 0;
//     while (tokens[i].type != (t_tokentype)-1)
//     {
//         const char *name = g_token_names[tokens[i].type] ?: "UNK";
//         printf("%s(%s)", name, tokens[i].value);
//         if (tokens[i+1].type != (t_tokentype)-1)
//             printf(" ");
//         i++;
//     }
//     printf("\n");
// }
