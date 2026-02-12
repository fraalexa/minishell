/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:47:19 by bepinhei          #+#    #+#             */
/*   Updated: 2026/02/12 03:03:37 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

int	process_shell_line(t_shell *shell)
{
	if (process_command_line(shell, shell->line) == FAILURE)
	{
		free(shell->line);
		shell->line = NULL;
		if (shell->heredoc)
		{
			free_heredoc(shell->heredoc);
			shell->heredoc = NULL;
		}
		return (1);
	}
	if (!shell->flag_exit)
	{
		free(shell->line);
		shell->line = NULL;
	}
	return (0);
}

int	handle_empty_line(t_shell *shell)
{
	if (!*shell->line)
	{
		shell->exit_status = 0;
		free(shell->line);
		return (2);
	}
	return (0);
}

int	handle_interactive_line(t_shell *shell)
{
	int	empty;

	empty = handle_empty_line(shell);
	if (empty == 2)
		return (0);
	if (empty)
		return (1);
	if (isatty(STDIN_FILENO))
		add_history(shell->line);
	return (process_shell_line(shell));
}
