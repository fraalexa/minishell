/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:46:33 by bepinhei          #+#    #+#             */
/*   Updated: 2026/02/12 03:55:51 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

char	get_quote_char(int quote_state)
{
	if (quote_state == 1)
		return ('\'');
	else
		return ('"');
}

int	should_concatenate_token(t_token **tokens, char *input, int start,
		int quote_state)
{
	return (quote_state == 0 && start > 0
		&& !is_whitespace(input[start - 1]) && token_lstlast(*tokens)
		&& (token_lstlast(*tokens)->type == TOKEN_WORD
			|| token_lstlast(*tokens)->type == TOKEN_VAR));
}

int	handle_concatenation(t_token **tokens, char *word, int quote_state)
{
	t_token	*last_token;
	char	*combined;

	last_token = token_lstlast(*tokens);
	combined = ft_strjoin(last_token->value, word);
	if (combined)
	{
		free(last_token->value);
		last_token->value = combined;
		if (ft_strchr(word, '$') && quote_state != 1)
			last_token->type = TOKEN_VAR;
	}
	free(word);
	if (combined)
		return (1);
	return (0);
}

char	*create_word_substr(char *input, int start, int len, int quote_state)
{
	char	*word;

	if (len == 0)
	{
		if (quote_state == 0)
			return (NULL);
		word = ft_strdup("");
	}
	else
		word = ft_substr(input, start, len);
	return (word);
}

int	merge_adjacent_tokens(t_token *last_token)
{
	t_token	*temp;
	char	*combined;

	if (!last_token || !last_token->next)
		return (1);
	combined = ft_strjoin(last_token->value, last_token->next->value);
	if (combined)
	{
		free(last_token->value);
		last_token->value = combined;
		temp = last_token->next;
		last_token->next = temp->next;
		free(temp->value);
		free(temp);
	}
	return (1);
}
