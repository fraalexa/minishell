/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepinhei <bepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:43:49 by bepinhei          #+#    #+#             */
/*   Updated: 2025/10/25 20:43:49 by bepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

int	is_variable_match(const char *env_var, const char *var_name)
{
	int	len;

	len = ft_strlen(var_name);
	return (ft_strncmp(env_var, var_name, len) == 0
		&& (env_var[len] == '=' || env_var[len] == '\0'));
}

int	remove_variable(char ***envp, char *var)
{
	int	j;
	int	found;

	j = 0;
	found = 0;
	while ((*envp)[j] && !found)
	{
		if (is_variable_match((*envp)[j], var))
		{
			found = 1;
			free((*envp)[j]);
			while ((*envp)[j + 1])
			{
				(*envp)[j] = (*envp)[j + 1];
				j++;
			}
			(*envp)[j] = NULL;
		}
		else
			j++;
	}
	return (found);
}

int	builtin_unset(char **argv, char ***envp)
{
	int	i;

	i = 1;
	if (!argv || !envp || !*envp)
		return (0);
	if (!argv[1])
		return (0);
	while (argv[i])
	{
		if (argv[i][0] && argv[i][0] != '-')
			remove_variable(envp, argv[i]);
		i++;
	}
	return (0);
}
