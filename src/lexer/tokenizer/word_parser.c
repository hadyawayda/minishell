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

void word_parser(const char *in, int *i, char **cur)
{
    char *tmp;

    while (in[*i] && !ft_isdelimiter(in[*i])
           && !is_operator_char(in[*i]) && in[*i] != '\''
           && in[*i] != '"')
    {
        if (in[*i] == '$')
            handle_expansion(in, i, cur);
        else
        {
            tmp = append_char(*cur, in[*i]);
            free(*cur);
            *cur = tmp;
            (*i)++;
        }
    }
}
