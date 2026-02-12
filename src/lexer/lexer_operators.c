/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepinhei <bepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:46:23 by bepinhei          #+#    #+#             */
/*   Updated: 2025/10/25 21:45:29 by bepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

int	handle_pipe(t_token **tokens, int *i)
{
	token_lstadd_back(tokens, token_new(TOKEN_PIPE, "|", 0));
	(*i)++;
	return (1);
}

int	handle_less(t_token **tokens, char *input, int *i)
{
	(*i)++;
	if (input[*i] == '<')
	{
		token_lstadd_back(tokens, token_new(TOKEN_HEREDOC, "<<", 0));
		(*i)++;
	}
	else
		token_lstadd_back(tokens, token_new(TOKEN_REDIR_IN, "<", 0));
	return (1);
}

int	handle_greater(t_token **tokens, char *input, int *i)
{
	(*i)++;
	if (input[*i] == '>')
	{
		token_lstadd_back(tokens, token_new(TOKEN_REDIR_APPEND, ">>", 0));
		(*i)++;
	}
	else
		token_lstadd_back(tokens, token_new(TOKEN_REDIR_OUT, ">", 0));
	return (1);
}

int	handle_operators(t_token **tokens, char *input, int *i)
{
	if (input[*i] == '|')
		return (handle_pipe(tokens, i));
	else if (input[*i] == '<')
		return (handle_less(tokens, input, i));
	else if (input[*i] == '>')
		return (handle_greater(tokens, input, i));
	return (0);
}
