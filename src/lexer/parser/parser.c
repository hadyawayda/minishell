/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:13:59 by hawayda           #+#    #+#             */
/*   Updated: 2025/05/05 21:43:11 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

/* width of the top bar */

// #define COL_W 23
// #define COL_GAP 4

// static void	repeat(int n, const char *s)
// {
// 	while (n--)
// 		fputs(s, stdout);
// }

// static void	print_job_header(int bg, int width)
// {
// 	int label_len = bg ? 9 : 3;                 /* "Job (bg)" vs "Job" */
// 	int pad_each = (width - label_len - 6) / 2; /* 6 = box chars + spaces */
// 	fputs("  ", stdout);
// 	repeat(pad_each, "─");
// 	fputs("┌─ Job", stdout);
// 	if (bg)
// 		fputs(" (bg)", stdout);
// 	fputs(" ─┐", stdout);
// 	repeat(pad_each, "─");
// 	putchar('\n');
// }

// static void	print_top_spine(int total_w)
// {
// 	repeat(total_w / 2 + 2, " "); /* +2 for left indent */
// 	fputs("│\n", stdout);
// }

// static void	print_joint_row(int n_cmd)
// {
// 	fputs("   ", stdout);
// 	for (int k = 0; k < n_cmd; k++)
// 	{
// 		if (k == 0)
// 			fputs("┌", stdout);
// 		else if (k == n_cmd - 1)
// 			fputs("┐", stdout);
// 		else
// 			fputs("┬", stdout);
// 		repeat(COL_W - 2, "─");
// 		if (k != n_cmd - 1)
// 			fputs("┴", stdout);
// 		if (k != n_cmd - 1)
// 			repeat(COL_GAP, " ");
// 	}
// 	putchar('\n');
// }

// static void	print_empty_row(int n_cmd)
// {
// 	fputs("   ", stdout);
// 	for (int k = 0; k < n_cmd; k++)
// 	{
// 		fputs("│", stdout);
// 		repeat(COL_W - 2, " ");
// 		fputs("│", stdout);
// 		if (k != n_cmd - 1)
// 			repeat(COL_GAP, " ");
// 	}
// 	putchar('\n');
// }

// static void	print_cmd_label(int which, int n_cmd, const char *label)
// {
// 	int	lablen;
// 	int	left;

// 	fputs("   ", stdout);
// 	for (int k = 0; k < n_cmd; k++)
// 	{
// 		fputs("│", stdout);
// 		if (k == which)
// 		{
// 			lablen = (int)strlen(label);
// 			left = (COL_W - 2 - lablen) / 2;
// 			repeat(left, " ");
// 			printf("%s", label);
// 			repeat(COL_W - 2 - left - lablen, " ");
// 		}
// 		else
// 			repeat(COL_W - 2, " ");
// 		fputs("│", stdout);
// 		if (k != n_cmd - 1)
// 			repeat(COL_GAP, " ");
// 	}
// 	putchar('\n');
// }

// static void	print_redir_line(int which, int n_cmd, t_redir *r)
// {
// 			char buf[COL_W - 2] = "";

// 	fputs("   ", stdout);
// 	for (int k = 0; k < n_cmd; k++)
// 	{
// 		fputs("│", stdout);
// 		if (k == which && r)
// 		{
// 			if (r->kind == R_IN)
// 				snprintf(buf, sizeof buf, "redir: < %s", r->target);
// 			else if (r->kind == R_OUT)
// 				snprintf(buf, sizeof buf, "redir: > %s", r->target);
// 			else if (r->kind == R_APPEND)
// 				snprintf(buf, sizeof buf, "redir: >> %s", r->target);
// 			else
// 				snprintf(buf, sizeof buf, "redir: << (heredoc)");
// 			printf("%-*s", COL_W - 2, buf);
// 		}
// 		else
// 			repeat(COL_W - 2, " ");
// 		fputs("│", stdout);
// 		if (k != n_cmd - 1)
// 			repeat(COL_GAP, " ");
// 	}
// 	putchar('\n');
// }

// /* ─────────── public: call after parse_tokens() ─────────── */
// void	visualize_job_box(t_job *job)
// {
// 	int	n_cmd;
// 	int	total_w;
// 	int	idx;
// 		char preview[COL_W - 2] = "";

// 	if (!job || !job->first)
// 		return ;
// 	n_cmd = 0;
// 	for (t_command *c = job->first; c; c = c->next)
// 		n_cmd++;
// 	total_w = n_cmd * COL_W + (n_cmd - 1) * COL_GAP;
// 	print_job_header(job->first->background, total_w);
// 	print_top_spine(total_w);
// 	print_joint_row(n_cmd);
// 	print_empty_row(n_cmd);
// 	idx = 0;
// 	for (t_command *cmd = job->first; cmd; cmd = cmd->next, idx++)
// 	{
// 		print_cmd_label(idx, n_cmd, "Command");
// 		/* argv preview */
// 		if (cmd->argv && cmd->argv[0])
// 		{
// 			strncat(preview, cmd->argv[0], sizeof preview - 1);
// 			if (cmd->argv[1])
// 			{
// 				strncat(preview, " ", sizeof preview - 1);
// 				strncat(preview, cmd->argv[1], sizeof preview - 1);
// 			}
// 		}
// 		print_cmd_label(idx, n_cmd, preview[0] ? preview : "(empty)");
// 		if (cmd->redirs)
// 			print_redir_line(idx, n_cmd, cmd->redirs);
// 	}
// 	putchar('\n');
// }

void	free_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type != (t_tokentype)-1)
	{
		free(tokens[i].value);
		i++;
	}
	free(tokens);
}

void	visualize_heredoc_tokens(t_token tokens[])
{
	int	i;

	for (i = 0; tokens[i].type != (t_tokentype)-1; i++)
	{
		if (tokens[i].type == T_REDIR_HERE && tokens[i].heredoc)
			printf("%s", tokens[i].heredoc);
		else
			printf("%s", tokens[i].value);
		if (tokens[i + 1].type != (t_tokentype)-1)
			putchar(' ');
	}
	putchar('\n');
}

void	parser(t_shell *shell, t_token *tokens)
{
	t_ast *root;

	if (!tokens)
		return ;
	if (check_syntax(tokens) < 0)
	{
		free_tokens(tokens);
		return ;
	}
	collect_heredocs(shell, tokens);
	visualize_heredoc_tokens(tokens);
	root = build_ast(tokens);
	traverse_ast(root);
	free_tokens(tokens);
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
