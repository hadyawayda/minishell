/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:24:18 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/22 03:52:20 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

int dollar_parser(const char *in, int *i, char **cur, bool in_dquotes)
{
    if (in[*i] != '$')
        return 0;

    /* ---------- locale $"..."  (only if not already in ")  -------- */
    if (!in_dquotes && in[*i + 1] == '"')
    {
        (*i) += 2;                           /* skip $ and "          */
        while (in[*i] && in[*i] != '"')
        {
          /* literal $$  → append "$$" and skip both chars */
          if (in[*i] == '$' && in[*i + 1] == '$')
          {
            *cur = append_char(*cur, '$');
            *cur = append_char(*cur, '$');
            (*i) += 2;
            continue;
          }
          if (in[*i] == '$')               /* $VAR expansion        */
              handle_expansion(in, i, cur);
          else
          {
            *cur = append_char(*cur, in[*i]);
            (*i)++;
          }
        }
        if (in[*i] != '"') return -1;        /* unclosed              */
        (*i)++;                              /* skip closing "        */
        return 0;
    }

    /* ---------- ANSI‑C $'...'  ----------------------------------- */
    if (in[*i + 1] == '\'')
    {
        (*i) += 2;                           /* skip $'               */
        while (in[*i] && in[*i] != '\'')
        {
            if (in[*i] == '$' && in[*i + 1] == '$')
            {   *cur = append_char(*cur, '$');
                *cur = append_char(*cur, '$');
                (*i) += 2;
            }
            else
              *cur = append_char(*cur, in[*i]);  (*i)++;
        }
        if (in[*i] != '\'') return -1;
        (*i)++;                              /* skip closing '        */
        return 0;
    }

    /* ---------- literal "$" inside an outer double‑quote ---------- */
    if (in_dquotes && in[*i + 1] == '"')
      *cur = append_char(*cur, '$');  (*i)++;  return 0;

    /* ---------- ordinary single‑$ expansion ----------------------- */
    /* treat $$ outside quotes as literal "$$" (skip both)           */
    if (in[*i + 1] == '$')
    {   *cur = append_char(*cur, '$');
        *cur = append_char(*cur, '$');
        (*i) += 2;
        return 0;
    }

    handle_expansion(in, i, cur);
    return 0;
}
