/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepinhei <bepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:47:44 by bepinhei          #+#    #+#             */
/*   Updated: 2025/10/25 21:45:29 by bepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

int	args_count(char **args)
{
	int	count;

	count = 0;
	if (!args)
		return (0);
	while (args[count])
		count++;
	return (count);
}

char	**args_add(char **args, char *new_arg)
{
	int		count;
	char	**new_args;
	int		i;

	count = args_count(args);
	new_args = (char **)malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[i] = strdup(new_arg);
	if (!new_args[i])
	{
		free(new_args);
		return (NULL);
	}
	new_args[i + 1] = NULL;
	if (args)
		free(args);
	return (new_args);
}

char	**args_dup(char **args)
{
	int		count;
	char	**new_args;
	int		i;

	count = args_count(args);
	new_args = (char **)malloc(sizeof(char *) * (count + 1));
	if (!new_args)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_args[i] = strdup(args[i]);
		if (!new_args[i])
		{
			while (--i >= 0)
				free(new_args[i]);
			free(new_args);
			return (NULL);
		}
		i++;
	}
	new_args[i] = NULL;
	return (new_args);
}
