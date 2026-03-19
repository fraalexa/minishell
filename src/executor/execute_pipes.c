/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepinhei <bepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:44:16 by bepinhei          #+#    #+#             */
/*   Updated: 2025/10/25 20:44:16 by bepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

static void	handle_pipe_left_child(t_shell *shell, t_ast_node *node,
	int *pipe_fd)
{
	int	status;

	restore_child_signals();
	shell->in_child_exec = true;
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	status = execute_ast_impl(shell, node->left);
	child_exit(shell, status);
}

static void	handle_pipe_right_child(t_shell *shell, t_ast_node *node,
	int *pipe_fd)
{
	int	status;

	restore_child_signals();
	shell->in_child_exec = true;
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	status = execute_ast_impl(shell, node->right);
	child_exit(shell, status);
}

static int	execute_pipe_children(t_shell *shell, t_ast_node *node,
	int *pipe_fd)
{
	pid_t	left_pid;
	pid_t	right_pid;
	int		right_status;

	left_pid = fork();
	if (left_pid == -1)
		return (FAILURE);
	if (left_pid == 0)
		handle_pipe_left_child(shell, node, pipe_fd);
	right_pid = fork();
	if (right_pid == -1)
		return (waitpid(left_pid, NULL, 0), FAILURE);
	if (right_pid == 0)
		handle_pipe_right_child(shell, node, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &right_status, 0);
	if (WIFEXITED(right_status))
		return (WEXITSTATUS(right_status));
	if (WIFSIGNALED(right_status))
		return (128 + WTERMSIG(right_status));
	return (SUCCESS);
}

static int	setup_pipe_execution(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
		return (FAILURE);
	return (SUCCESS);
}

int	execute_pipe_node(t_shell *shell, t_ast_node *node)
{
	int		pipe_fd[2];

	if (setup_pipe_execution(pipe_fd) == FAILURE)
		return (FAILURE);
	return (execute_pipe_children(shell, node, pipe_fd));
}
