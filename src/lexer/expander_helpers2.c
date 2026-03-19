/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 04:20:00 by fraalexa          #+#    #+#             */
/*   Updated: 2026/02/27 04:26:18 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

char	*expand_unquoted_string(char *str, t_shell *shell)
{
	char	*result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	return (process_quoted_chars(result, str, shell));
}

static char	*expand_dquote_content(char *result, char *str,
				t_shell *shell, int *i)
{
	if (str[*i] == '$' && str[*i + 1])
		result = append_expansion(result, str, shell, i);
	else
	{
		result = append_char_to_result(result, str[*i]);
		(*i)++;
	}
	return (result);
}

char	*expand_double_quoted(char *str, t_shell *shell)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		result = expand_dquote_content(result, str, shell, &i);
		if (!result)
			return (NULL);
	}
	return (result);
}
