/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepinhei <bepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:45:58 by bepinhei          #+#    #+#             */
/*   Updated: 2025/10/25 21:45:29 by bepinhei         ###   ########.fr       */
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

char	*process_quoted_chars(char *result, char *inner, t_shell *shell)
{
	int	i;
	int	squote;
	int	dquote;

	i = 0;
	squote = 0;
	dquote = 0;
	while (inner[i])
	{
		if (update_quote_state(inner[i], &squote, &dquote))
			i++;
		else if (inner[i] == '$' && !squote && inner[i + 1])
			result = append_expansion(result, inner, shell, &i);
		else
		{
			result = append_char_to_result(result, inner[i]);
			i++;
		}
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

char	*expand_unquoted_string(char *str, t_shell *shell)
{
	char	*result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	return (process_quoted_chars(result, str, shell));
}

char	*get_env_value(char *name, t_shell *shell)
{
	int		i;
	int		len;
	char	*env_entry;

	if (!name || !shell || !shell->envp)
		return (NULL);
	if (ft_strcmp(name, "0") == 0)
		return (ft_strdup("minishell"));
	len = ft_strlen(name);
	i = 0;
	while (shell->envp[i])
	{
		env_entry = shell->envp[i];
		if (ft_strncmp(env_entry, name, len) == 0 && env_entry[len] == '=')
			return (env_entry + len + 1);
		i++;
	}
	return (NULL);
}
