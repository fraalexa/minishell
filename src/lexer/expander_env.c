/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 00:00:00 by fraalexa          #+#    #+#             */
/*   Updated: 2026/02/25 03:34:38 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

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
