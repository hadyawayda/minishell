/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 04:48:14 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/30 21:36:27 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "core.h"

int					quote_parser(t_shell *sh, const char *in, t_tokenstate *st);
int					is_operator_char(char c);
int					dollar_parser(t_shell *sh, const char *in, t_tokenstate *st);
int					check_syntax(t_token tokens[]);
int					need_expand(const char *val);
int					get_matches(const char *pattern, char ***matches_out);
int					match_bracket(const char **sp, const char **pp);

char				*ft_strjoin_char(char *s1, char c);
char				*append_char(char *s1, char c);
char				*clean_pattern(const char *pat);

void				free_string_array(char **array);
void				operator_parser(const char *in, t_token tokens[],
						t_tokenstate *st);
void				word_parser(const char *in, t_tokenstate *st);
void				handle_expansion(t_shell *sh, const char *in, int *i,
						char **cur);
void				append_char_inplace(char **dst, char c, int *i);
void				flush_current(t_token tokens[], t_tokenstate *st);
void				append_literal_dollars(const char *in, int *i, char **cur);
void				skip_whitespaces_and_flush(const char *input, t_tokenstate *st,
						t_token tokens[]);
void				collect_heredocs(t_shell *shell, t_token tokens[]);
void				expand_wildcards(t_token tokens[]);
void				strip_unexpandable(char *val);

t_token			*input_tokenizer(t_shell *shell, char *input);

#endif
