/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepinhei <bepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:45:23 by bepinhei          #+#    #+#             */
/*   Updated: 2025/10/25 20:45:23 by bepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

void	sigquit_handler(int sig)
{
	(void)sig;
}

void	sigint_handler(int sig)
{
	(void)sig;
	if (waitpid(-1, NULL, WNOHANG) == -1)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_signal = 130;
}

static void	sigint_heredoc_handler(int sig)
{
	(void)sig;
	g_signal = 130;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	setup_signals(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signals_heredoc(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = sigint_heredoc_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	signal(SIGQUIT, SIG_IGN);
}
