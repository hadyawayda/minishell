/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:13:59 by hawayda           #+#    #+#             */
/*   Updated: 2025/02/16 22:20:34 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/core.h"
#include "../lexer.h"

void	parser(t_shell *shell, char *input)
{
	(void)shell;
	tokenizer(input);
}

// modify the parser to print nothing when using unset and not print a new line when expanding an unset env variable
// void	parser(t_shell *shell, char *input)
// {
// 	char	*expanded_input;
// 	char	**args;
// 	int		i;
// 	char	*key;
// 	char	*value;
// 	char	*equal_sign;

// 	if (!input || !shell)
// 		return ;
// 	if (!ft_strchr(input, '$'))
// 		expanded_input = ft_strdup(input);
// 	else
// 		expanded_input = expand_variables(input, shell);
// 	if (!expanded_input)
// 		return ;
// 	args = ft_split_charset(expanded_input, " ");
// 	if (!args || !args[0])
// 	{
// 		free(expanded_input);
// 		return ;
// 	}
// 	printf("%s\n", expanded_input);
// 	if (ft_strcmp(args[0], "env") == 0)
// 		list_env(shell->env);
// 	else if (ft_strcmp(args[0], "export") == 0)
// 	{
// 		if (!args[1])
// 			list_export(shell->env);
// 		else
// 		{
// 			i = 1;
// 			while (args[i])
// 			{
// 				equal_sign = ft_strchr(args[i], '=');
// 				if (equal_sign)
// 				{
// 					*equal_sign = '\0';
// 					key = args[i];
// 					value = equal_sign + 1;
// 					if (value[0] == '"' && value[ft_strlen(value) - 1] == '"')
// 					{
// 						value[ft_strlen(value) - 1] = '\0';
// 						value++;
// 					}
// 					if (!is_valid_varname(key))
// 						printf("minishell: export: `%s=%s': not a valid identifier\n",
// 							key, value);
// 					else
// 						add_env_variable(&(shell->env), key, value);
// 					*equal_sign = '=';
// 				}
// 				else if (!is_valid_varname(args[i]))
// 					printf("minishell: export: `%s': not a valid identifier\n",
// 						args[i]);
// 				i++;
// 			}
// 		}
// 	}
// 	else if (ft_strcmp(args[0], "unset") == 0)
// 	{
// 		i = 1;
// 		while (args[i])
// 		{
// 			unset_env_variable(&(shell->env), args[i]);
// 			printf("unsetting %s\n", args[i]);
// 			i++;
// 		}
// 	}
// 	free(expanded_input);
// 	free_string_array(args);
// }

// t_ast_node	*parse_input(char *input)
// {
// 	t_ast_node			*root;
// 	t_ast_node			*current;
// 	t_ast_node			*pipe_node;
// 	t_redirection_type	redir_type;
// 	t_ast_node			*redir_node;
// 	char				**argv;

// 	// Tokenize the input (e.g., using strtok or a custom tokenizer).
// 	char **tokens = tokenize(input); // This is just a placeholder function
// 	root = NULL;
// 	current = NULL;
// 	for (int i = 0; tokens[i]; i++)
// 	{
// 		if (strcmp(tokens[i], "|") == 0)
// 		{
// 			// Create a pipe node with the current command as the left child
// 			pipe_node = create_pipe_node(root, NULL);
// 			root = pipe_node;
// 			current = NULL; // Prepare for the next command after the pipe
// 		}
// 		else if (strcmp(tokens[i], "<") == 0 || strcmp(tokens[i], ">") == 0
// 			|| strcmp(tokens[i], ">>") == 0 || strcmp(tokens[i], "<<") == 0)
// 		{
// 			// Handle redirections
// 			redir_type = get_redirection_type(tokens[i]);
// 			redir_node = create_redirection_node(current, redir_type,
// 					tokens[++i]);
// 			current = redir_node;
// 		}
// 		else
// 		{
// 			// Handle a command or arguments
// 			if (current == NULL)
// 			{
// 				// Start a new command
// 				argv = get_command_arguments(tokens, i);
// 				// Placeholder function to get command arguments
// 				current = create_command_node(argv, NULL, NULL, 0);
// 				if (!root)
// 				{
// 					root = current;
// 				}
// 				else
// 				{
// 					root->pipe.right = current;
// 					// Set the right child of the pipe
// 				}
// 			}
// 		}
// 	}
// 	return (root);
// }
