#include "../../includes/minishell.h"

#ifndef PARSER_H
# define PARSER_H

void	parser(t_shell *shell, char *input);
void	free_string_array(char **array);

#endif