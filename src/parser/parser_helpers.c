/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepinhei <bepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:48:14 by bepinhei          #+#    #+#             */
/*   Updated: 2025/10/25 21:45:29 by bepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

int	match_token(t_parser *parser, t_token_type type)
{
	if (!parser->current)
		return (0);
	return (parser->current->type == type);
}

void	parser_error(t_parser *parser, char *msg)
{
	parser->error = 1;
	if (msg)
		parser->error_msg = ft_strdup(msg);
	else
		parser->error_msg = NULL;
}

t_token	*peek_token(t_parser *parser)
{
	return (parser->current);
}

t_token	*next_token(t_parser *parser)
{
	if (parser->current)
		parser->current = parser->current->next;
	return (parser->current);
}

int	is_command_end(t_parser *parser)
{
	if (!parser->current)
		return (1);
	if (parser->current->type == TOKEN_PIPE)
		return (1);
	if (parser->current->type == TOKEN_EOF)
		return (1);
	return (0);
}
