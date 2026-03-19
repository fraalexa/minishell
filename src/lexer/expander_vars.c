/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepinhei <bepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:46:11 by bepinhei          #+#    #+#             */
/*   Updated: 2025/10/25 21:45:29 by bepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

char	*get_expanded_value(char *var_name, int name_len, t_shell *shell)
{
	char	*value;
	char	*var_name_dup;

	if (!var_name || !shell)
		return (NULL);
	if (name_len == 1 && var_name[0] == '?')
		return (ft_itoa(shell->exit_status));
	var_name_dup = ft_substr(var_name, 0, name_len);
	if (!var_name_dup)
		return (NULL);
	value = get_env_value(var_name_dup, shell);
	free(var_name_dup);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

static char	*handle_dollar_only(char *result, int *i)
{
	char	*temp;

	temp = ft_charjoin(result, '$');
	(*i)++;
	return (temp);
}

static char	*handle_var_expansion(char *result, char *var_name, int name_len,
		t_shell *shell)
{
	char	*value;
	char	*temp;

	value = get_expanded_value(var_name, name_len, shell);
	if (!value)
	{
		free(result);
		return (NULL);
	}
	temp = ft_strjoin(result, value);
	free(result);
	free(value);
	return (temp);
}

char	*append_expansion(char *result, char *str, t_shell *shell, int *i)
{
	char	*var_name;
	int		name_len;
	char	*temp;

	if (!result || !str || !shell)
		return (NULL);
	var_name = get_var_name(str + *i, &name_len);
	if (!var_name)
		return (handle_dollar_only(result, i));
	temp = handle_var_expansion(result, var_name, name_len, shell);
	if (!temp)
		return (NULL);
	*i += name_len + 1;
	return (temp);
}
