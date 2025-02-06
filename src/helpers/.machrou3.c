/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .machrou3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:22:00 by hawayda           #+#    #+#             */
/*   Updated: 2024/09/27 01:36:28 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <ctype.h>
#include <stdio.h>

int	check_space(char character)
{
	return (character == ' ' || character == '\t' || character == '\v'
		|| character == '\r');
}

void	skip_spaces(char *str, int *i)
{
	while (str[*i] && check_space(str[*i]))
		(*i)++;
}

int	is_redirection_operator(char *str, int i)
{
	if (str[i] == '>' || str[i] == '<')
		return (1);
	return (0);
}

void	handle_redirection_operator(char *str, int *i, int *words)
{
	(*words)++;
	ft_printf("Redirection Operator '");
	ft_printf("%c", str[*i]);
	(*i)++;
	if (str[*i] == '>' || str[*i] == '<')
	{
		ft_printf("%c", str[*i]);
		(*i)++;
	}
	if (str[*i] == '&')
	{
		ft_printf("%c", str[*i]);
		(*i)++;
	}
	ft_printf("' | Word count: %d\n", *words);
}

void	handle_word(char *str, int *i, int *words)
{
	char	in_quote;

	in_quote = 0;
	(*words)++;
	ft_printf("Word '");
	while (str[*i] && (!check_space(str[*i]) && !is_redirection_operator(str,
				*i)))
	{
		if (str[*i] == '\\' && str[*i + 1])
		{
			(*i)++;
			ft_printf("%c", str[*i]);
			(*i)++;
			continue ;
		}
		if ((str[*i] == '"' || str[*i] == '\''))
		{
			if (in_quote == 0)
				in_quote = str[(*i)++];
			else if (in_quote == str[*i])
				in_quote = 0, (*i)++;
			else
				ft_printf("%c", str[(*i)++]);
			continue ;
		}
		ft_printf("%c", str[(*i)++]);
	}
	ft_printf("' | Word count: %d\n", *words);
}

int	count_words(char *str)
{
	int	i;
	int	words;

	i = 0, words = 0;
	while (str[i])
	{
		skip_spaces(str, &i);
		if (!str[i])
			break ;
		if (is_redirection_operator(str, i))
		{
			handle_redirection_operator(str, &i, &words);
			skip_spaces(str, &i);
			if (str[i])
				handle_word(str, &i, &words);
			continue ;
		}
		handle_word(str, &i, &words);
	}
	return (words);
}

int	main(void)
{
	// char *str1 = "command > output.txt";
	// char *str2 = "command 2> error.log";
	// char *str3 = "command >& output.txt";
	// char *str4 = "command > 2file.txt";
	// char *str5 = "command > &output.txt";
	// char *str6 = " 2>&1";
	// char *str7 = " 2 >& 1";
	// int count1 = count_words(str1);
	// int count2 = count_words(str2);
	// int count3 = count_words(str3);
	// int count4 = count_words(str4);
	// int count5 = count_words(str5);
	// int count6 = count_words(str6);
	// int count7 = count_words(str7);
	// ft_printf("Total words/commands: %d\n", count1);
	// ft_printf("Total words/commands: %d\n", count2);
	// ft_printf("Total words/commands: %d\n", count3);
	// ft_printf("Total words/commands: %d\n", count4);
	// ft_printf("Total words/commands: %d\n", count5);
	// ft_printf("Total words/commands: %d\n", count6);
	// ft_printf("Total words/commands: %d\n", count7);
	return (0);
}
