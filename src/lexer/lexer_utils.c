/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 04:41:09 by fraalexa          #+#    #+#             */
/*   Updated: 2026/02/12 04:41:11 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

int	ft_isoperator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	skip_whitespace_z(char *input, int *i)
{
	while (input[*i] && is_whitespace(input[*i]))
		(*i)++;
}

int	advance_word_pos(char *input, int *i, int quote_state, char quote_char)
{
	if (quote_state == 0)
	{
		while (input[*i] && !is_whitespace(input[*i])
			&& !ft_isoperator(input[*i]) && input[*i] != '\''
			&& input[*i] != '"')
			(*i)++;
	}
	else
	{
		while (input[*i] && input[*i] != quote_char)
			(*i)++;
		if (!input[*i])
			return (0);
	}
	return (1);
}
