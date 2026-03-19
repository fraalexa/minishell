/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:45:54 by bepinhei          #+#    #+#             */
/*   Updated: 2026/02/27 04:18:13 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

int	expand_command_args(t_ast_node *ast, t_shell *shell)
{
	char	*expanded;
	int		quoted;
	int		i;

	i = 0;
	while (ast->args && ast->args[i])
	{
		quoted = 0;
		if (ast->arg_quotes)
			quoted = ast->arg_quotes[i];
		expanded = expand_string(ast->args[i], quoted, shell);
		if (!expanded)
			return (0);
		free(ast->args[i]);
		ast->args[i] = expanded;
		i++;
	}
	return (1);
}

int	expand_redirections(t_redir_node *redir, t_shell *shell)
{
	char	*expanded;

	while (redir)
	{
		if (redir->type != NODE_HEREDOC && redir->file)
		{
			expanded = expand_string(redir->file, 0, shell);
			if (!expanded)
				return (0);
			free(redir->file);
			redir->file = expanded;
		}
		redir = redir->next;
	}
	return (1);
}
