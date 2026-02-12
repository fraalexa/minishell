/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:44:30 by bepinhei          #+#    #+#             */
/*   Updated: 2026/02/12 04:37:39 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

static char	*heredoc_prompt(void)
{
	if (isatty(STDIN_FILENO))
		return ("> ");
	return ("");
}

static char	*read_stdin_line(void)
{
	char		*line;
	char		c;
	ssize_t		bytes;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	while (1)
	{
		bytes = read(STDIN_FILENO, &c, 1);
		if (bytes <= 0 || c == '\n')
			break ;
		line = ft_charjoin(line, c);
		if (!line)
			return (NULL);
	}
	if (bytes <= 0 && line[0] == '\0')
		return (free(line), NULL);
	return (line);
}

static char	*read_heredoc_line(void)
{
	if (!isatty(STDIN_FILENO))
		return (read_stdin_line());
	return (readline(heredoc_prompt()));
}

static int	write_heredoc_line(int fd, char *line)
{
	if (!line)
		return (SUCCESS);
	if (write(fd, line, ft_strlen(line)) == -1)
		return (FAILURE);
	if (write(fd, "\n", 1) == -1)
		return (FAILURE);
	return (SUCCESS);
}

static int	heredoc_warn_eof(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putendl_fd("')", 2);
	return (SUCCESS);
}

static int	heredoc_handle_payload(t_shell *shell, int fd, char *line,
		int expand_vars)
{
	char	*payload;
	int		res;

	if (!expand_vars)
		payload = line;
	else
	{
		payload = expand_unquoted_string(line, shell);
		free(line);
		if (!payload)
			return (FAILURE);
	}
	res = write_heredoc_line(fd, payload);
	if (expand_vars)
		free(payload);
	else
		free(line);
	return (res);
}

static int	heredoc_fill_pipe(t_shell *shell, t_redir_node *redir, int fd)
{
	char	*line;
	int		expand_vars;

	expand_vars = (redir->quoted == 0);
	while (1)
	{
		line = read_heredoc_line();
		if (!line)
		{
			if (g_signal == 130)
			{
				shell->exit_status = 130;
				g_signal = 0;
				return (FAILURE);
			}
			return (heredoc_warn_eof(redir->file));
		}
		if (ft_strcmp(line, redir->file) == 0)
			return (free(line), SUCCESS);
		if (heredoc_handle_payload(shell, fd, line, expand_vars) == FAILURE)
			return (FAILURE);
	}
}

static void	restore_stdin(int stdin_copy)
{
	if (stdin_copy == -1)
		return ;
	dup2(stdin_copy, STDIN_FILENO);
	close(stdin_copy);
}

static int	apply_input_redirection(t_shell *shell, char *file)
{
	shell->fd_in = open(file, O_RDONLY);
	if (shell->fd_in == -1)
	{
		safe_putstr_fd("minishell: ", 2);
		safe_putstr_fd(file, 2);
		safe_putstr_fd(": ", 2);
		ft_putendl_fd((char *)strerror(errno), 2);
		return (FAILURE);
	}
	dup2(shell->fd_in, STDIN_FILENO);
	close(shell->fd_in);
	return (SUCCESS);
}

static int	apply_output_redirection(t_shell *shell, char *file, int append)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	shell->fd_out = open(file, flags, 0644);
	if (shell->fd_out == -1)
	{
		safe_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)file, 2);
		ft_putstr_fd((char *)": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (FAILURE);
	}
	dup2(shell->fd_out, STDOUT_FILENO);
	close(shell->fd_out);
	return (SUCCESS);
}

static int	apply_heredoc_redirection(t_shell *shell, t_redir_node *redir)
{
	int		pipe_fd[2];
	int		stdin_copy;
	int		res;

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
	restore_stdin(stdin_copy);
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

static int	setup_backup_fds(int *original_fds)
{
	if (original_fds[0] == -1)
		original_fds[0] = dup(STDIN_FILENO);
	if (original_fds[1] == -1)
		original_fds[1] = dup(STDOUT_FILENO);
	return (SUCCESS);
}

int	apply_redirections(t_shell *shell, t_redir_node *redir, int *original_fds)
{
	int	result;

	setup_backup_fds(original_fds);
	while (redir)
	{
		if (redir->type == NODE_REDIR_IN)
			result = apply_input_redirection(shell, redir->file);
		else if (redir->type == NODE_REDIR_OUT)
			result = apply_output_redirection(shell, redir->file, 0);
		else if (redir->type == NODE_REDIR_APPEND)
			result = apply_output_redirection(shell, redir->file, 1);
		else if (redir->type == NODE_HEREDOC)
			result = apply_heredoc_redirection(shell, redir);
		else
			result = SUCCESS;
		if (result == FAILURE)
			return (FAILURE);
		redir = redir->next;
	}
	return (SUCCESS);
}
