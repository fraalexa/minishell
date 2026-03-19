/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:44:30 by bepinhei          #+#    #+#             */
/*   Updated: 2026/02/25 03:29:33 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

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
