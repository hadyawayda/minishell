/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:13:59 by hawayda           #+#    #+#             */
/*   Updated: 2025/06/18 02:04:03 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

char	*expand_line_heredoc(t_shell *shell, const char *line);
char	*make_chunk(t_shell *shell, const char *line, int expand,
			size_t *chunk_len);
char	*append_buf(char *buf, size_t len, const char *chunk, size_t chunk_len);
char	*append_chunk(char **buf, size_t *tot, char *tmp, ssize_t n);
void	heredoc_child(int fd[2], char *delim, int expand, t_shell *sh);

int		check_operator_sequence(t_token tokens[]);
int		check_dollar_paren(t_token tokens[]);
int		is_redir(t_tokentype t);
int		check_leading_token(t_token tokens[]);

void	visualize_tree(t_ast *root);
void	free_tokens(t_token *tokens);
void	visualize_heredoc_tokens(t_token tokens[]);
void	free_ast(t_ast *node);
void	print_tokens(t_token *tokens);
void	count_opts(t_parser *p, int *n_opts);
void	fill_cmd_node(t_parser *p, t_ast *node);
void	handle_word_token(t_ast *node, t_token *tok, t_argnode **args_head,
			t_argnode **args_tail);
void	shift_left(t_token tok[], int idx);

t_ast	*parser(t_shell *shell, t_token *tokens);
t_ast	*parse_expression(t_parser *p);
t_ast	*parse_pipe(t_parser *p);
t_ast	*parse_factor(t_parser *p);
t_ast	*parse_command(t_parser *p);
t_ast	*build_ast(t_token *tokens);
t_ast	*alloc_cmd_node(int n_opts);

t_token	*peek(t_parser *p);
t_token	*next(t_parser *p);

#endif
