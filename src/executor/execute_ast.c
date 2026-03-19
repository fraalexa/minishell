/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:44:06 by bepinhei          #+#    #+#             */
/*   Updated: 2026/03/17 02:08:53 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

static int	execute_command_node(t_shell *shell, t_ast_node *node)
{
	int			original_fds[2];
	int			status;
	t_cmd_group	cmd_type;

	original_fds[0] = -1;
	original_fds[1] = -1;
	if (!shell || !shell->envp)
		return (FAILURE);
	if (apply_redirections(shell, node->redirects, original_fds) == FAILURE)
		return (restore_redirections(original_fds), shell->exit_status = 1, 1);
	if (shell->non_interactive)
		fflush(stdout);
	if (!node->args || !node->args[0])
	{
		restore_redirections(original_fds);
		return (SUCCESS);
	}
	cmd_type = get_cmd_type(node->args[0]);
	if (cmd_type != CMD_EXEC)
		status = execute_builtin(shell, node->args, cmd_type);
	else
		status = execute_external(shell, node->args);
	restore_redirections(original_fds);
	return (status);
}

static int	handle_node_types(t_shell *shell, t_ast_node *ast)
{
	int	status;

	status = FAILURE;
	if (ast->type == NODE_COMMAND)
		status = execute_command_node(shell, ast);
	else if (ast->type == NODE_PIPE)
		status = execute_pipe_node(shell, ast);
	return (status);
}

static void	setup_execution_environment(void)
{
	signals_executor();
}

static void	finalize_execution(void)
{
	if (!isatty(STDIN_FILENO))
		fflush(stdout);
}

int	execute_ast_impl(t_shell *shell, t_ast_node *ast)
{
	int	status;

	if (!ast)
		return (FAILURE);
	if (!shell || !shell->in_child_exec)
		setup_execution_environment();
	status = handle_node_types(shell, ast);
	finalize_execution();
	return (status);
}
