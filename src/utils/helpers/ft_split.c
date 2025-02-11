/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:18:29 by fel-ghaz          #+#    #+#             */
/*   Updated: 2024/09/27 00:44:10 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_token(char *str, int i, char **token)
{
	int		start;
	char	in_quote;
	int		handled;

	start = i;
	in_quote = 0;
	while (str[i])
	{
		i = handle_quotes(str, i, &in_quote, &handled);
		if (handled)
			continue ;
		if (!in_quote && (check_space(str[i]) || is_separator(str, i)))
			break ;
		i++;
	}
	*token = ft_strndup(&str[start], i - start);
	return (i);
}
int	get_separator(char *str, int i, char **token)
{
	int	start;

	start = i;
	while (str[i] && is_separator(str, i))
		i++;
	*token = strndup(&str[start], i - start);
	return (i);
}

int	add_token(data *data, char *token)
{
	data->tokens[data->count++] = token;
	if (data->count >= data->size)
	{
		data->size *= 2;
		data->tokens = realloc(data->tokens, data->size * sizeof(char *));
		if (!data->tokens)
			return (0);
	}
	return (1);
}

int	process_next_token(char *str, int i, data *data)
{
	char	*token;

	i = skip_spaces(str, i);
	if (!str[i])
		return (i);
	if (is_separator(str, i))
		i = get_separator(str, i, &token);
	else
		i = get_token(str, i, &token);
	if (!add_token(data, token))
		return (-1);
	return (i);
}

char	**ft_split_charset(char *str)
{
	int		i;
	int		j;
	data	data;

	i = 0;
	j = 0;
	data.size = 10;
	data.count = 0;
	data.tokens = malloc(data.size * sizeof(char *));
	if (!data.tokens)
		return (NULL);
	while (str[i])
	{
		i = process_next_token(str, i, &data);
		if (i == -1)
		{
			while (j < data.count)
				free(data.tokens[j++]);
			free(data.tokens);
			return (NULL);
		}
	}
	data.tokens[data.count] = NULL;
	return (data.tokens);
}
