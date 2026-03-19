/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepinhei <bepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:46:03 by bepinhei          #+#    #+#             */
/*   Updated: 2025/10/25 21:45:29 by bepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

char	*ft_charjoin(char *s, char c)
{
	char	*result;
	int		len;
	int		i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	result = malloc(len + 2);
	if (!result)
	{
		free(s);
		return (NULL);
	}
	i = 0;
	while (s[i])
	{
		result[i] = s[i];
		i++;
	}
	result[i] = c;
	result[i + 1] = '\0';
	free(s);
	return (result);
}

static char	*handle_special_vars(char *str, int *len)
{
	if (str[1] == '?')
	{
		*len = 1;
		return (str + 1);
	}
	if (str[1] == '0')
	{
		*len = 1;
		return (str + 1);
	}
	return (NULL);
}

static int	is_valid_var_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

static int	var_name_length(char *str)
{
	int	i;

	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i - 1);
}

char	*get_var_name(char *str, int *len)
{
	char	*special;

	if (!str || str[0] != '$')
		return (NULL);
	special = handle_special_vars(str, len);
	if (special)
		return (special);
	if (!str[1])
	{
		*len = 0;
		return (NULL);
	}
	if (!is_valid_var_start(str[1]))
	{
		*len = 0;
		return (NULL);
	}
	*len = var_name_length(str);
	return (str + 1);
}
