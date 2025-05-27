/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:01:06 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/27 21:35:07 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

/*
**  Prints every token.value, showing any WILD_UNEXPANDABLE bytes
**  as “\x1F” so you can see them in your terminal.
*/
// void	debug_print_tokens(t_token tokens[])
// {
// 	int		i;
// 	char	*val;

// 	i = 0;
// 	while (tokens[i].type != (t_tokentype)-1)
// 	{
// 		val = tokens[i].value;
// 		printf("token[%d]: '", i);
// 		while (val && *val)
// 		{
// 			if (*val == WILD_UNEXPANDABLE)
// 				printf("\\x%02x", (unsigned char)*val);
// 			else
// 				putchar(*val);
// 			val++;
// 		}
// 		printf("'\n");
// 		i++;
// 	}
// }

/*
**  Shift all tokens[from..] right by `n` slots to make room.
*/
void	shift_tokens_right(t_token tokens[], int from, int n)
{
	int	end;

	end = 0;
	while (tokens[end].type != (t_tokentype)-1)
		end++;
	/* move the sentinel too */
	while (end >= from)
	{
		tokens[end + n] = tokens[end];
		end--;
	}
}

/*
**  Insert a new word-token at `pos` whose value is `s`.
*/
void	insert_token(t_token tokens[], int pos, const char *s)
{
	tokens[pos].type = T_WORD;
	tokens[pos].value = ft_strdup(s);
	tokens[pos].is_quoted = false;
	tokens[pos].heredoc = NULL;
	/* you can set is_expandable[pos] here if you track it */
}

/*
**  The main expansion loop.
*/
void	expand_wildcards(t_token tokens[])
{
	int		j;
	char	**matches;
	int		mcount;
	int		k;

	j = 0;
	while (tokens[j].type != (t_tokentype)-1)
	{
		if (need_expand(tokens[j].value))
		{
			mcount = get_matches(tokens[j].value, &matches);
			if (mcount > 0)
			{
				free(tokens[j].value);
				tokens[j].value = ft_strdup(matches[0]);
				if (mcount > 1)
				{
					shift_tokens_right(tokens, j + 1, mcount - 1);
					k = 1;
					while (k < mcount)
					{
						insert_token(tokens, j + k, matches[k]);
						k++;
					}
				}
				j += mcount;
			}
			else
			{
				strip_unexpandable(tokens[j].value);
				j++;
			}
			k = 0;
			while (k < mcount)
				free(matches[k++]);
			free(matches);
		}
		else
			j++;
	}
}
