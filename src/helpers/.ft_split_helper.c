/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .ft_split_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:01:26 by fel-ghaz          #+#    #+#             */
/*   Updated: 2024/09/27 01:35:42 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
int	check_space(char character)
{
	if (character == ' ' || character == '\t' || character == '\v'
		|| character == '\r')
		return (1);
	return (0);
}
int	check_single_tokens(char character)
{
	if (character == '<' || character == '>' || character == '|'
		|| character == ' ')
	{
		ft_printf("single:%c\n", character);
		return (1);
	}
	return (0);
}
int	check_double_tokens(char *str, int i)
{
	if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i
			+ 1] == '<'))
	{
		ft_printf("double:%c%c\n", str[i], str[i + 1]);
		return (1);
	}
	return (0);
}
int	count_tokens(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			// i++;
			while (str[i] && str[i] != '"')
				i++;
		}
		if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i
				+ 1] == '<'))
		{
			i += 2;
			count++;
		}
		else if (str[i] == '>' || str[i] == '<' || str[i] == '|'
			|| str[i] == ' ')
		{
			i++;
			ft_printf("hi");
			count++;
			while (str[i] && str[i] == ' ')
				i++;
		}
		i++;
	}
	return (count);
}

int	char_is_separator(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

int	count_words(char *str, char *charset)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((char_is_separator(str[i], charset)) && (char_is_separator(str[i
					+ 1], charset)))
		{
			words++;
			ft_printf("%c%d\n", str[i], words);
			i++;
		}
		else if (char_is_separator(str[i], charset))
		{
			words++;
			ft_printf("%c%d\n", str[i], words);
		}
		else if ((!char_is_separator(str[i], charset) && !check_space(str[i]))
			&& (char_is_separator(str[i + 1], charset) || str[i + 1] == ' '
				|| !str[i + 1]))
		{
			words++;
			ft_printf("%c%d\n", str[i], words);
		}
		i++;
	}
	return (words);
}
int	main(void)
{
	char	*str;
	char	*charset;
	int		count;

	str = "echo >> file.tt | \"ju\"grep|a < b >> w > | a \"pa\"|\"|ttern\"";
	// char *str = "echo|hi|bbbbb >fffff";
	charset = "|><";
	count = count_words(str, charset);
	ft_printf("%d", count);
}
