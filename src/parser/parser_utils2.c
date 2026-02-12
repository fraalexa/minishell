/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:48:30 by bepinhei          #+#    #+#             */
/*   Updated: 2026/02/12 03:03:37 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

t_ast_node	*create_pipe_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*pipe_node;

	pipe_node = ast_new_node(NODE_PIPE);
	if (!pipe_node)
	{
		ast_free(left);
		ast_free(right);
		return (NULL);
	}
	pipe_node->left = left;
	pipe_node->right = right;
	return (pipe_node);
}

t_ast_node	*ast_new_node(t_node_type type)
{
	t_ast_node	*node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->redirects = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_redir_node	*redir_new_node(t_node_type type, char *file)
{
	t_redir_node	*redir;

	redir = (t_redir_node *)malloc(sizeof(t_redir_node));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = strdup(file);
	redir->quoted = 0;
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	redir->next = NULL;
	return (redir);
}
