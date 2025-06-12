/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_matcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:28:34 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/12 22:59:56 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
**  Recursive, full‐featured glob matcher.
*/
int	match_pattern(const char *sp, const char *pp)
{
	if (!*pp)
		return (!*sp);
	if (*pp == '*')
	{
		while (pp[1] == '*')
			pp++;
		return (match_pattern(sp, pp + 1) || (*sp && match_pattern(sp + 1,
					pp)));
	}
	if (*pp == '?')
	{
		if (!*sp)
			return (0);
		return (match_pattern(sp + 1, pp + 1));
	}
	if (*pp == '[')
	{
		if (match_bracket(&sp, &pp))
			return (match_pattern(sp, pp));
		return (0);
	}
	if (*sp && *pp == *sp)
		return (match_pattern(sp + 1, pp + 1));
	return (0);
}

/*
**  Count how many entries in CWD match `pat`.
*/
int	count_dir_matches(const char *pat)
{
	DIR				*dir;
	struct dirent	*ent;
	int				count;

	count = 0;
	dir = opendir(".");
	if (!dir)
		return (0);
	ent = readdir(dir);
	while (ent)
	{
		if (!ft_strcmp(ent->d_name, ".") || !ft_strcmp(ent->d_name, "..")
			|| (ent->d_name[0] == '.' && pat[0] != '.'))
		{
			ent = readdir(dir);
			continue ;
		}
		if (match_pattern(ent->d_name, pat))
			count++;
		ent = readdir(dir);
	}
	closedir(dir);
	return (count);
}

/*
**  Fill ms[0..] with strdup’d names of entries matching `pat`.
*/
void	collect_dir_matches(const char *pat, char **ms)
{
	DIR				*dir;
	struct dirent	*ent;
	int				i;

	i = 0;
	dir = opendir(".");
	if (!dir)
		return ;
	ent = readdir(dir);
	while (ent)
	{
		if (!ft_strcmp(ent->d_name, ".") || !ft_strcmp(ent->d_name, "..")
			|| (ent->d_name[0] == '.' && pat[0] != '.'))
		{
			ent = readdir(dir);
			continue ;
		}
		if (match_pattern(ent->d_name, pat))
			ms[i++] = ft_strdup(ent->d_name);
		ent = readdir(dir);
	}
	closedir(dir);
}

/*
**  Scan CWD for matches to the cleaned pattern, using only malloc.
*/
int	get_matches(const char *pattern, char ***matches_out)
{
	char	*pat;
	char	**ms;
	int		count;

	pat = clean_pattern(pattern);
	count = count_dir_matches(pat);
	if (count <= 0)
	{
		free(pat);
		*matches_out = NULL;
		return (0);
	}
	ms = malloc(sizeof(*ms) * count);
	collect_dir_matches(pat, ms);
	free(pat);
	*matches_out = ms;
	return (count);
}
