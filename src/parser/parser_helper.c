/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepinhei <bepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:48:11 by bepinhei          #+#    #+#             */
/*   Updated: 2025/10/25 21:45:29 by bepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

void	redir_add_back(t_redir_node **redir_list, t_redir_node *new_redir)
{
	t_redir_node	*current;

	if (!redir_list || !new_redir)
		return ;
	if (!*redir_list)
	{
		*redir_list = new_redir;
		return ;
	}
	current = *redir_list;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

int	redir_count(t_redir_node *redir)
{
	int	count;

	count = 0;
	while (redir)
	{
		count++;
		redir = redir->next;
	}
	return (count);
}

int	ast_has_pipes(t_ast_node *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_PIPE)
		return (1);
	if (ast_has_pipes(node->left) || ast_has_pipes(node->right))
		return (1);
	return (0);
}

int	ast_count_pipes(t_ast_node *node)
{
	int	count;

	if (!node)
		return (0);
	count = 0;
	if (node->type == NODE_PIPE)
		count = 1;
	count += ast_count_pipes(node->left);
	count += ast_count_pipes(node->right);
	return (count);
}
