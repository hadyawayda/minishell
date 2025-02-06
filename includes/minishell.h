/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:09:17 by fel-ghaz          #+#    #+#             */
/*   Updated: 2024/09/28 20:12:00 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _XOPEN_SOURCE 700

# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	char			**tokens;
	char			*data;
	struct s_data	*left;
	struct s_data	*right;
	int				count;
	int				size;
	int				SHLVL;
}					data;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef enum e_ast_type {
    AST_COMMAND,
    AST_PIPE,
    AST_REDIRECTION
} t_ast_type;

// Enum to define types of redirections
typedef enum e_redirection_type {
    REDIR_INPUT,      // <
    REDIR_OUTPUT,     // >
    REDIR_APPEND,     // >>
    REDIR_HEREDOC     // <<
} t_redirection_type;

// Structure to define a command node
typedef struct s_command {
    char **argv;          // Command and arguments
    char *input_file;     // Input file for redirection
    char *output_file;    // Output file for redirection
    t_redirection_type output_type; // Type of output redirection
} t_command;

// Structure to define an AST node
typedef struct s_ast_node {
    t_ast_type type;              // Type of the node (command, pipe, etc.)
    union {
        t_command *command;       // Command node
        struct {
            struct s_ast_node *left;  // Left child (e.g., the command before the pipe)
            struct s_ast_node *right; // Right child (e.g., the command after the pipe)
        } pipe;
        struct {
            struct s_ast_node *command_node; // Command to redirect
            t_redirection_type type;         // Type of redirection
            char *file;                      // File to redirect to
        } redirection;
    };
} t_ast_node;

// typedef struct nodee
// {
// 	int				data;
// 	struct nodee	*next;
// 	struct nodee	*previous;
// }					t_node;

void				ft_echo(char **splitted);
void				ft_pwd(void);
void				ft_exit(void);
void				ft_cd(char *input);
void				ft_strcopy(char *dest, char *src);
void				ft_strcat(char *dest, char *source);
void				setup_signal_handlers(void);

char				**ft_split_charset(char *str);
char				*ft_strndup(const char *s, size_t n);

int					check_space(char c);
int					is_separator(char *str, int i);
int					skip_spaces(char *str, int i);
int					handle_quotes(char *str, int i, char *in_quote,
						int *handled);
int					get_token(char *str, int i, char **token);
int					get_separator(char *str, int i, char **token);
int					add_token(data *data, char *token);
int					process_next_token(char *str, int i, data *data);
int					ft_strcmp(char *s1, char *s2);

#endif
