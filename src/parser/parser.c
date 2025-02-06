/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:13:59 by hawayda           #+#    #+#             */
/*   Updated: 2024/09/28 20:14:10 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_node	*parse_input(char *input)
{
	t_ast_node			*root;
	t_ast_node			*current;
	t_ast_node			*pipe_node;
	t_redirection_type	redir_type;
	t_ast_node			*redir_node;

	// Tokenize the input (e.g., using strtok or a custom tokenizer).
	char **tokens = tokenize(input); // This is just a placeholder function
	root = NULL;
	current = NULL;
	for (int i = 0; tokens[i]; i++)
	{
		if (strcmp(tokens[i], "|") == 0)
		{
			// Create a pipe node with the current command as the left child
			pipe_node = create_pipe_node(root, NULL);
			root = pipe_node;
			current = NULL; // Prepare for the next command after the pipe
		}
		else if (strcmp(tokens[i], "<") == 0 || strcmp(tokens[i], ">") == 0
			|| strcmp(tokens[i], ">>") == 0 || strcmp(tokens[i], "<<") == 0)
		{
			// Handle redirections
			redir_type = get_redirection_type(tokens[i]);
			redir_node = create_redirection_node(current, redir_type,
					tokens[++i]);
			current = redir_node;
		}
		else
		{
			// Handle a command or arguments
			if (current == NULL)
			{
				// Start a new command
				char **argv = get_command_arguments(tokens, i);
					// Placeholder function to get command arguments
				current = create_command_node(argv, NULL, NULL, 0);
				if (!root)
				{
					root = current;
				}
				else
				{
					root->pipe.right = current;
						// Set the right child of the pipe
				}
			}
		}
	}
	return (root);
}
