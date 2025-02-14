/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:12:46 by hawayda           #+#    #+#             */
/*   Updated: 2024/09/28 20:12:57 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Function to create a command AST node
t_ast_node *create_command_node(char **argv, char *input_file, char *output_file, t_redirection_type output_type) {
    t_ast_node *node = malloc(sizeof(t_ast_node));
    if (!node)
        return NULL;

    node->type = AST_COMMAND;
    node->command = malloc(sizeof(t_command));
    if (!node->command) {
        free(node);
        return NULL;
    }

    node->command->argv = argv;
    node->command->input_file = input_file ? strdup(input_file) : NULL;
    node->command->output_file = output_file ? strdup(output_file) : NULL;
    node->command->output_type = output_type;

    return node;
}

// Function to create a pipe AST node
t_ast_node *create_pipe_node(t_ast_node *left, t_ast_node *right) {
    t_ast_node *node = malloc(sizeof(t_ast_node));
    if (!node)
        return NULL;

    node->type = AST_PIPE;
    node->pipe.left = left;
    node->pipe.right = right;

    return node;
}

// Function to create a redirection AST node
t_ast_node *create_redirection_node(t_ast_node *command_node, t_redirection_type type, char *file) {
    t_ast_node *node = malloc(sizeof(t_ast_node));
    if (!node)
        return NULL;

    node->type = AST_REDIRECTION;
    node->redirection.command_node = command_node;
    node->redirection.type = type;
    node->redirection.file = file ? strdup(file) : NULL;

    return node;
}
