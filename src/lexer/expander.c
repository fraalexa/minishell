/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:46:17 by bepinhei          #+#    #+#             */
/*   Updated: 2026/02/12 03:23:49 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

char	*expand_string(char *str, int quoted, t_shell *shell)
{
	int	len;

	(void)quoted;
	if (!str || !shell)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
		return (ft_substr(str, 1, len - 2));
	if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
		return (expand_quoted_string(str, shell));
	return (expand_unquoted_string(str, shell));
}

int	filter_empty_args(char **args)
{
	int	read_idx;
	int	write_idx;

	if (!args)
		return (1);
	read_idx = 0;
	write_idx = 0;
	while (args[read_idx])
	{
		if (args[read_idx][0] != '\0')
		{
			if (read_idx != write_idx)
				args[write_idx] = args[read_idx];
			write_idx++;
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
		filter_empty_args(ast->args);
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
