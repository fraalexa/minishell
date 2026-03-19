/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:45:58 by bepinhei          #+#    #+#             */
/*   Updated: 2026/02/27 04:26:18 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

char	*append_char_to_result(char *result, char c)
{
	char	*temp;

	temp = ft_charjoin(result, c);
	if (!temp)
	{
		free(result);
		return (NULL);
	}
	return (temp);
}

static int	update_quote_state(char c, int *squote, int *dquote)
{
	if (c == '\'' && !(*dquote))
	{
		*squote = !(*squote);
		return (1);
	}
	if (c == '"' && !(*squote))
	{
		*dquote = !(*dquote);
		return (1);
	}
	return (0);
}

static char	*process_char(char *res, char *str, t_shell *sh, t_vars *v)
{
	if (update_quote_state(str[v->i], &v->sq, &v->dq))
		v->i++;
	else if (str[v->i] == '$' && !v->sq && str[v->i + 1])
		res = append_expansion(res, str, sh, &v->i);
	else
	{
		res = append_char_to_result(res, str[v->i]);
		v->i++;
	}
	return (res);
}

char	*process_quoted_chars(char *result, char *inner, t_shell *shell)
{
	t_vars	v;

	v.i = 0;
	v.sq = 0;
	v.dq = 0;
	while (inner[v.i])
	{
		result = process_char(result, inner, shell, &v);
		if (!result)
			return (NULL);
	}
	return (result);
}

char	*expand_quoted_string(char *str, t_shell *shell)
{
	char	*result;
	char	*inner;
	int		len;

	len = ft_strlen(str);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	inner = ft_substr(str, 1, len - 2);
	if (!inner)
	{
		free(result);
		return (NULL);
	}
	result = process_quoted_chars(result, inner, shell);
	free(inner);
	return (result);
}
