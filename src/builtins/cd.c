/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:42:24 by bepinhei          #+#    #+#             */
/*   Updated: 2026/03/19 03:54:52 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

int	find_env_var(char **envp, const char *var)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(var);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0 && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	update_env_var(char **envp, const char *var, const char *value)
{
	int		index;
	char	*new_var;
	size_t	var_len;
	size_t	value_len;

	var_len = ft_strlen(var);
	value_len = ft_strlen(value);
	new_var = malloc(var_len + value_len + 2);
	if (!new_var)
		return ;
	ft_strlcpy(new_var, var, var_len + 1);
	ft_strlcat(new_var, "=", var_len + 2);
	ft_strlcat(new_var, value, var_len + value_len + 2);
	index = find_env_var(envp, var);
	if (index != -1)
	{
		free(envp[index]);
		envp[index] = new_var;
	}
}

static int	cd_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
		return (printf("shell: cd: HOME not set\n"), 1);
	if (chdir(home) != 0)
		return (perror("shell: cd"), 1);
	return (0);
}

int	builtin_cd(char **argv, char **envp)
{
	char	cur[PATH_MAX];
	char	new[PATH_MAX];

	if (!argv || !envp)
		return (1);
	if (getcwd(cur, sizeof(cur)) == NULL)
		return (perror("shell: getcwd"), 1);
	if (!argv[1] || ft_strcmp(argv[1], "~") == 0)
	{
		if (cd_home() != 0)
			return (1);
	}
	else if (argv[2])
		return (safe_putstr_fd(" too many arguments\n", 2), 1);
	else if (chdir(argv[1]) != 0)
		return (perror("shell: cd"), 1);
	if (getcwd(new, sizeof(new)) == NULL)
		return (perror("shell: getcwd"), 1);
	update_env_var(envp, "OLDPWD", cur);
	update_env_var(envp, "PWD", new);
	return (0);
}
