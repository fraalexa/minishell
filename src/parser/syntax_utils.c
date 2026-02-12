/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepinhei <bepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:48:39 by bepinhei          #+#    #+#             */
/*   Updated: 2025/10/25 21:45:29 by bepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

t_node_type	token_to_node_type(t_token_type token_type)
{
	if (token_type == TOKEN_REDIR_IN)
		return (NODE_REDIR_IN);
	if (token_type == TOKEN_REDIR_OUT)
		return (NODE_REDIR_OUT);
	if (token_type == TOKEN_REDIR_APPEND)
		return (NODE_REDIR_APPEND);
	if (token_type == TOKEN_HEREDOC)
		return (NODE_HEREDOC);
	return (NODE_COMMAND);
}
