/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_matcher_helpers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:28:34 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/27 21:35:00 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

/*
**  Return 1 if `val` contains a '*' not preceded by our unexpandable marker.
*/
int	need_expand(const char *val)
{
	int	i;

	i = 0;
	while (val[i])
	{
		if (val[i] == '*' && (i == 0 || val[i - 1] != WILD_UNEXPANDABLE))
			return (1);
		i++;
	}
	return (0);
}

/*
**  Remove all marker bytes so that a quoted "*" becomes a real '*' in the final
**  literal.
*/
void	strip_unexpandable(char *val)
{
	int	r;
	int	w;

	r = 0;
	w = 0;
	while (val[r])
	{
		if (val[r] == WILD_UNEXPANDABLE)
			r++;
		else
			val[w++] = val[r++];
	}
	val[w] = '\0';
}

/*
**  Strip our unexpandable markers so that quoted '*' remain literal.
*/
char	*clean_pattern(const char *pat)
{
	char	*out;
	int		r;
	int		w;

	out = ft_strdup("");
	r = 0;
	w = 0;
	while (pat[r])
	{
		if (pat[r] == WILD_UNEXPANDABLE)
			r++;
		else
			append_char_inplace(&out, pat[r++], &w);
	}
	return (out);
}
