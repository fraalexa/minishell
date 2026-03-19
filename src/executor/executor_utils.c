/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:44:47 by bepinhei          #+#    #+#             */
/*   Updated: 2026/02/12 02:29:36 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

char	*check_direct_path(char *cmd)
{
	if (cmd[0])
	{
		if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
		{
			if (access(cmd, F_OK | X_OK) == 0)
				return (ft_strdup(cmd));
			return (NULL);
		}
	}
	return (NULL);
}

char	*search_in_env_path(char *cmd, char **envp)
{
	char	**full_path;
	char	*half_path;
	char	*path;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	full_path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (full_path[i])
	{
		half_path = ft_strjoin(full_path[i], "/");
		path = ft_strjoin(half_path, cmd);
		free(half_path);
		if (access(path, F_OK | X_OK) == 0)
			return (free_arg(full_path), path);
		free(path);
		i++;
	}
	return (free_arg(full_path), NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	*path;

	path = check_direct_path(cmd);
	if (path)
		return (path);
	path = search_in_env_path(cmd, envp);
	return (path);
}
