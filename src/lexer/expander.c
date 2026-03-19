/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:46:17 by bepinhei          #+#    #+#             */
/*   Updated: 2026/03/10 02:35:58 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

char	*expand_string(char *str, int quoted, t_shell *shell)
{
	char	*result;

	(void)quoted;
	if (!str || !shell)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	return (process_quoted_chars(result, str, shell));
}

int	filter_empty_args(char **args, int *quotes)
{
	int	read_idx;
	int	write_idx;

	if (!args)
		return (1);
	read_idx = 0;
	write_idx = 0;
	while (args[read_idx])
	{
		if (args[read_idx][0] || (quotes && quotes[read_idx]))
		{
			if (quotes)
				quotes[write_idx] = quotes[read_idx];
			args[write_idx++] = args[read_idx];
		}
		else
			free(args[read_idx]);
		read_idx++;
	}
	args[write_idx] = NULL;
	return (1);
}

int	expand_ast(t_ast_node *ast, t_shell *shell)
{
	if (!ast || !shell)
		return (0);
	if (ast->type == NODE_COMMAND)
	{
		if (!expand_command_args(ast, shell))
			return (0);
		filter_empty_args(ast->args, ast->arg_quotes);
		if (!expand_redirections(ast->redirects, shell))
			return (0);
	}
	else if (ast->type == NODE_PIPE)
	{
		if (!expand_ast(ast->left, shell) || !expand_ast(ast->right, shell))
			return (0);
	}
	return (1);
}
