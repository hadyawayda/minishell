/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 05:58:57 by hawayda           #+#    #+#             */
/*   Updated: 2024/09/27 04:57:49 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig; // Suppress unused parameter warning
	// Print a new line to clear current input and prompt again
	ft_printf("\n");
	rl_replace_line("", 0); // Clear the line
	rl_on_new_line();       // Move to a new line
	rl_redisplay();         // Redisplay the prompt
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa;

	// Handle SIGINT (Ctrl + C)
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handle_sigint; // Set the handler function
	sigemptyset(&sa.sa_mask);      // Don't block any other signals
	sa.sa_flags = SA_RESTART;
	// Automatically restart interrupted system calls
	sigaction(SIGINT, &sa, NULL); // Set the handler for SIGINT
	// Ignore SIGQUIT (Ctrl + \)
	sa.sa_handler = SIG_IGN;       // Ignore the signal
	sigaction(SIGQUIT, &sa, NULL); // Set the handler for SIGQUIT
}
