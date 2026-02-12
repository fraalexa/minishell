/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by berna             #+#    #+#             */
/*   Updated: 2026/02/12 04:44:47 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

int	process_command_line(t_shell *shell, char *line)
{
	t_token		*tokens;
	t_ast_node	*ast;

	if (!line || !*line)
	{
		shell->exit_status = 0;
		return (0);
	}
	tokens = lexer(line);
	if (!tokens)
		return (handle_lexer_failure(shell, line));
	ast = parse(tokens);
	token_lstclear(&tokens);
	if (!ast)
	{
		shell->exit_status = 2;
		return (FAILURE);
	}
	return (process_ast(shell, ast));
}

int	execute_ast(t_shell *shell, t_ast_node *ast)
{
	int	status;

	if (!ast)
		return (FAILURE);
	status = execute_ast_impl(shell, ast);
	shell->exit_status = status;
	if (!isatty(STDIN_FILENO))
		fflush(stdout);
	return (status);
}
