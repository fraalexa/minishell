/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepinhei <bepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:48:32 by bepinhei          #+#    #+#             */
/*   Updated: 2025/10/25 21:45:29 by bepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

t_ast_node	*parse_command(t_parser *parser)
{
	t_ast_node	*cmd;

	cmd = ast_new_node(NODE_COMMAND);
	if (!cmd)
		return (NULL);
	while (!is_command_end(parser))
	{
		if (!process_token(parser, cmd))
		{
			ast_free(cmd);
			return (NULL);
		}
	}
	return (cmd);
}

t_ast_node	*parse_pipeline(t_parser *parser)
{
	t_ast_node	*left;
	t_ast_node	*right;

	left = parse_command(parser);
	if (!left)
		return (NULL);
	while (parser->current && parser->current->type == TOKEN_PIPE)
	{
		next_token(parser);
		right = parse_command(parser);
		if (!right)
		{
			ast_free(left);
			return (NULL);
		}
		left = create_pipe_node(left, right);
		if (!left)
			return (NULL);
	}
	return (left);
}

void	print_parser_error(t_parser *parser)
{
	if (parser->error_msg)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(parser->error_msg, 2);
		ft_putstr_fd("\n", 2);
		free(parser->error_msg);
		parser->error_msg = NULL;
	}
}

void	parser_init(t_parser *parser, t_token *tokens)
{
	parser->tokens = tokens;
	parser->current = tokens;
	parser->error = 0;
	parser->error_msg = NULL;
}

t_ast_node	*parse(t_token *tokens)
{
	t_parser	parser;
	t_ast_node	*ast;

	if (!validate_syntax(tokens))
		return (NULL);
	parser_init(&parser, tokens);
	ast = parse_pipeline(&parser);
	if (parser.error)
	{
		print_parser_error(&parser);
		ast_free(ast);
		return (NULL);
	}
	return (ast);
}
