/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepinhei <bepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:48:18 by bepinhei          #+#    #+#             */
/*   Updated: 2025/10/25 21:45:29 by bepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

int	validate_redirects(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current && TOKEN_EOF != current->type)
	{
		if (is_redir_token(current->type))
		{
			current = current->next;
			if (TOKEN_EOF == current->type || TOKEN_PIPE == current->type
				|| is_redir_token(current->type))
			{
				ft_putstr_fd("minishell: syntax error near unexpected token'\n",
					2);
				return (0);
			}
			continue ;
		}
		current = current->next;
	}
	return (1);
}

int	validate_pipes(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (TOKEN_PIPE == current->type)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (0);
	}
	while (current && current->type != TOKEN_EOF)
	{
		if (TOKEN_PIPE == current->type)
		{
			current = current->next;
			if (TOKEN_EOF == current->type || TOKEN_PIPE == current->type)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token \
					`|'\n", 2);
				return (0);
			}
			continue ;
		}
		current = current->next;
	}
	return (1);
}

int	validate_syntax(t_token *tokens)
{
	if (!tokens)
		return (0);
	if (TOKEN_EOF == tokens->type)
		return (1);
	if (!validate_pipes(tokens))
		return (0);
	if (!validate_redirects(tokens))
		return (0);
	return (1);
}

int	is_redir_type(t_node_type type)
{
	return (type == NODE_REDIR_IN || type == NODE_REDIR_OUT
		|| type == NODE_REDIR_APPEND || type == NODE_HEREDOC);
}

int	is_redir_token(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_HEREDOC);
}
