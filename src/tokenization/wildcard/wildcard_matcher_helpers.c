/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_matcher_helpers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:28:34 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/12 22:59:59 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

/*
**  Scan the contents of a […] class starting at p (just after '['),
**  updating *matched if **sp fits, and return the position of the ']'
**  or end-of-string.
*/
const char	*scan_bracket_content(const char *p, const char *sp, int *matched)
{
	while (*p && *p != ']')
	{
		if (p[1] == '-' && p[2] && p[2] != ']' && *sp >= *p && *sp <= p[2])
		{
			*matched = 1;
			p += 3;
		}
		else
		{
			if (*sp == *p)
				*matched = 1;
			p++;
		}
	}
	return (p);
}

/*
**  Consume a […] class at *pp and advance both *sp and *pp.
**  Returns 1 on class-match; 0 otherwise.
*/
int	match_bracket(const char **sp, const char **pp)
{
	int			neg;
	int			matched;
	const char	*p;

	neg = 0;
	matched = 0;
	p = *pp + 1;
	if (*p == '!' || *p == '^')
	{
		neg = 1;
		p++;
	}
	p = scan_bracket_content(p, *sp, &matched);
	if (*p != ']')
		return (0);
	if ((matched && !neg) || (!matched && neg))
	{
		(*sp)++;
		*pp = p + 1;
		return (1);
	}
	return (0);
}
