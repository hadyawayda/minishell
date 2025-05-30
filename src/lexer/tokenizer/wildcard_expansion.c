/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:01:06 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/30 20:33:43 by hawayda          ###   ########.fr       */
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
**  Build an env‐style linked list from matches[0..count-1].
*/
t_env	*matches_to_env_list(char **matches, int count)
{
	t_env	*head;
	t_env	*node;
	int		i;

	head = NULL;
	i = 0;
	while (i < count)
	{
		node = malloc(sizeof(*node));
		node->key = matches[i];
		node->value = NULL;
		node->next = head;
		head = node;
		i++;
	}
	return (head);
}

/*
**  Sort the array matches[0..count-1] in place, alphabetically.
*/
void	sort_matches(char **matches, int count)
{
	int		i;
	t_env	*tmp;
	t_env	*list;

	i = 0;
	list = matches_to_env_list(matches, count);
	sort_env_list(&list);
	while (list)
	{
		matches[i++] = list->key;
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

/*
**  Shift all tokens[from..] right by `n` slots to make room.
*/
void	shift_tokens_right(t_token tokens[], int from, int n)
{
	int	end;

	end = 0;
	while (tokens[end].type != (t_tokentype)-1)
		end++;
	while (end >= from)
	{
		tokens[end + n] = tokens[end];
		end--;
	}
}

/*
**  The main expansion loop.
**  Handles the “mcount > 0” block: replaces tokens[j] with matches[0]
**  and inserts the rest of the matches into the token stream.
**  Returns the new index to continue from.
*/
int	apply_matches(t_token tokens[], int j, char **matches, int mcount)
{
	int	k;

	free(tokens[j].value);
	tokens[j].value = ft_strdup(matches[0]);
	if (mcount > 1)
	{
		shift_tokens_right(tokens, j + 1, mcount - 1);
		k = 1;
		while (k < mcount)
		{
			tokens[j + k].type = T_WORD;
			tokens[j + k].value = ft_strdup(matches[k]);
			tokens[j + k].is_quoted = false;
			tokens[j + k].heredoc = NULL;
			k++;
		}
	}
	return (j + mcount);
}

/*
**  Loop through all tokens, call get_matches, then either
**  expand via apply_matches() or strip markers on no-match.
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
			if (mcount > 1)
				sort_matches(matches, mcount);
			if (mcount > 0)
				j = apply_matches(tokens, j, matches, mcount);
			else
				strip_unexpandable(tokens[j++].value);
			k = 0;
			while (k < mcount)
				free(matches[k++]);
			free(matches);
		}
		else
			j++;
	}
}
