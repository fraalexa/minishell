/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 04:40:52 by fraalexa          #+#    #+#             */
/*   Updated: 2026/02/12 04:40:53 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

static int	find_quote_end(char *line, int start, char quote)
{
	int	i;

	i = start + 1;
	while (line[i])
	{
		if (line[i] == quote)
			return (i);
		i++;
	}
	return (-1);
}

int	check_quote_error(char *line, char *quote)
{
	int		i;
	char	current;
	int		end;

	i = 0;
	*quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			current = line[i];
			end = find_quote_end(line, i, current);
			if (end == -1)
			{
				*quote = current;
				return (1);
			}
			i = end + 1;
		}
		else
			i++;
	}
	return (0);
}

void	print_quote_error(char quote)
{
	safe_putstr_fd("minishell: syntax error: unexpected EOF while looking ", 2);
	safe_putstr_fd("for matching `", 2);
	ft_putchar_fd(quote, 2);
	safe_putstr_fd("'\n", 2);
}

int	handle_lexer_failure(t_shell *shell, char *line)
{
	char	quote;

	if (check_quote_error(line, &quote))
		print_quote_error(quote);
	shell->exit_status = 2;
	return (FAILURE);
}

int	process_ast(t_shell *shell, t_ast_node *ast)
{
	int	status;

	if (!expand_ast(ast, shell))
	{
		ast_free(ast);
		shell->exit_status = 1;
		return (FAILURE);
	}
	if (ast->type == NODE_COMMAND && ast->args && (!ast->args[0]
			|| ast->args[0][0] == '\0'))
	{
		ast_free(ast);
		shell->exit_status = 0;
		return (0);
	}
	status = execute_ast(shell, ast);
	ast_free(ast);
	return (status);
}
