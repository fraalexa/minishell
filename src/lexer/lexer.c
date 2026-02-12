/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepinhei <bepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:46:39 by bepinhei          #+#    #+#             */
/*   Updated: 2025/10/25 21:45:29 by bepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

int	create_word_token(t_token **tokens, char *word, int quote_state)
{
	t_token_type	type;

	type = TOKEN_WORD;
	if (word && ft_strchr(word, '$') && quote_state != 1)
		type = TOKEN_VAR;
	token_lstadd_back(tokens, token_new(type, word, quote_state != 0));
	return (1);
}

int	handle_word(t_token **tokens, char *input, int *i, int quote_state)
{
	int		start;
	char	quote_char;
	char	*word;
	int		len;
	int		ret;
	int		is_heredoc_delim;
	t_token	*last;

	start = *i;
	quote_char = get_quote_char(quote_state);
	if (advance_word_pos(input, i, quote_state, quote_char) == 0)
		return (0);
	len = *i - start;
	if (quote_state != 0)
		(*i)++;
	last = token_lstlast(*tokens);
	is_heredoc_delim = (quote_state != 0 && last && last->type == TOKEN_HEREDOC);
	if (is_heredoc_delim)
	{
		if (len == 0)
			word = ft_strdup("");
		else
			word = ft_substr(input, start, len);
	}
	else
		word = create_word_substr(input, start, len, quote_state);
	if (!word && len == 0 && quote_state == 0)
		return (1);
	if (!word)
		return (0);
	if (should_concatenate_token(tokens, input, start, quote_state))
		return (handle_concatenation(tokens, word, quote_state));
	ret = create_word_token(tokens, word, quote_state);
	free(word);
	return (ret);
}

int	process_quote_open(t_token **tokens, char *input, int *i, int *quote_state)
{
	char	open_quote;
	int		result;
	t_token	*last_token;

	open_quote = input[*i];
	if (open_quote == '\'')
		*quote_state = 1;
	else
		*quote_state = 2;
	(*i)++;
	last_token = token_lstlast(*tokens);
	if (last_token && *i >= 2 && !is_whitespace(input[*i - 2]) 
		&& (last_token->type == TOKEN_WORD || last_token->type == TOKEN_VAR))
	{
		result = handle_word(tokens, input, i, *quote_state);
		if (result && (*tokens) && last_token->next)
			merge_adjacent_tokens(last_token);
		return (result);
	}
	return (handle_word(tokens, input, i, *quote_state));
}

int	lexer_loop(t_token **tokens, char *input, int *i, int *quote_state)
{
	skip_whitespace_z(input, i);
	if (!input[*i])
		return (0);
	if (*quote_state == 0 && (input[*i] == '\'' || input[*i] == '"'))
	{
		if (process_quote_open(tokens, input, i, quote_state) == 0)
			return (0);
		*quote_state = 0;
		return (1);
	}
	if (*quote_state == 0 && handle_operators(tokens, input, i))
		return (1);
	if (handle_word(tokens, input, i, *quote_state) == 0)
		return (0);
	*quote_state = 0;
	return (1);
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	int		i;
	int		quote_state;

	tokens = NULL;
	i = 0;
	quote_state = 0;
	if (!input)
		return (NULL);
	while (input[i])
	{
		if (lexer_loop(&tokens, input, &i, &quote_state) == 0)
			break ;
	}
	if (quote_state != 0)
	{
		token_lstclear(&tokens);
		return (NULL);
	}
	token_lstadd_back(&tokens, token_new(TOKEN_EOF, NULL, 0));
	return (tokens);
}
