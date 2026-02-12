/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:48:27 by bepinhei          #+#    #+#             */
/*   Updated: 2026/02/12 03:03:37 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

t_redir_node	*parse_single_redir(t_parser *parser)
{
	t_node_type		redir_type;
	t_redir_node	*redir;

	redir_type = token_to_node_type(parser->current->type);
	next_token(parser);
	if (!parser->current || parser->current->type == TOKEN_EOF)
	{
		parser_error(parser, "unexpected token after redirection");
		return (NULL);
	}
	redir = redir_new_node(redir_type, parser->current->value);
	if (!redir)
	{
		parser_error(parser, "memory allocation failed");
		return (NULL);
	}
	if (redir_type == NODE_HEREDOC)
		redir->quoted = parser->current->quoted;
	next_token(parser);
	return (redir);
}

int	handle_redirection(t_parser *parser, t_ast_node *cmd)
{
	t_redir_node	*redir;

	redir = parse_single_redir(parser);
	if (!redir)
		return (0);
	redir_add_back(&cmd->redirects, redir);
	return (1);
}

int	handle_argument(t_parser *parser, t_ast_node *cmd)
{
	char	*value;

	value = parser->current->value;
	cmd->args = args_add(cmd->args, value);
	if (!cmd->args)
		return (0);
	next_token(parser);
	return (1);
}

int	process_token(t_parser *parser, t_ast_node *cmd)
{
	if (is_redir_token(parser->current->type))
		return (handle_redirection(parser, cmd));
	else if (parser->current->type == TOKEN_WORD
		|| parser->current->type == TOKEN_VAR)
		return (handle_argument(parser, cmd));
	return (0);
}
