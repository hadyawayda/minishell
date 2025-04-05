/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabbas <nabbas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:04:57 by nabbas            #+#    #+#             */
/*   Updated: 2025/04/06 00:15:59 by nabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

enum	builtins
{
	bi_cd,
	bi_echo,
	bi_pwd,
	bi_unset,
	bi_env,
	bi_export,
	bi_exit
};

// Function Prototypes
void	start_shell(char *envp[]);
int		is_builtin(char *command);
int		execute_builtin(char **args, char *envp[]);
int		execute_command(char **args);
char	**split_input(const char *input);

#endif
