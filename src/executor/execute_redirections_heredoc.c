/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections_heredoc.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 00:00:00 by fraalexa          #+#    #+#             */
/*   Updated: 2026/02/27 04:18:13 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

char	*read_heredoc_line(void);
int		heredoc_warn_eof(char *delimiter);
int		is_heredoc_end(char *line, char *file);
int		write_heredoc_payload(t_shell *shell, int fd, char *line,
			int expand_vars);

static void	restore_stdin_copy(int stdin_copy)
{
	if (stdin_copy == -1)
		return ;
	dup2(stdin_copy, STDIN_FILENO);
	close(stdin_copy);
}

static int	heredoc_fill_pipe(t_shell *shell, t_redir_node *redir, int fd)
{
	char	*line;
	int		expand_vars;

	expand_vars = (redir->quoted != 1);
	while (1)
	{
		line = read_heredoc_line();
		if (!line)
			return (heredoc_warn_eof(redir->file));
		if (g_signal == 130)
		{
			free(line);
			shell->exit_status = 130;
			g_signal = 0;
			return (FAILURE);
		}
		if (is_heredoc_end(line, redir->file))
		{
			free(line);
			return (SUCCESS);
		}
		if (write_heredoc_payload(shell, fd, line, expand_vars) == FAILURE)
			return (FAILURE);
	}
}

int	apply_heredoc_redirection(t_shell *shell, t_redir_node *redir)
{
	int	pipe_fd[2];
	int	stdin_copy;
	int	res;

	if (!shell || !redir || !redir->file)
		return (FAILURE);
	stdin_copy = dup(STDIN_FILENO);
	if (stdin_copy == -1)
		return (FAILURE);
	if (pipe(pipe_fd) == -1)
		return (close(stdin_copy), FAILURE);
	setup_signals_heredoc();
	res = heredoc_fill_pipe(shell, redir, pipe_fd[1]);
	close(pipe_fd[1]);
	restore_stdin_copy(stdin_copy);
	setup_signals();
	if (res == FAILURE)
	{
		close(pipe_fd[0]);
		return (FAILURE);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	return (SUCCESS);
}
