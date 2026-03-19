/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepinhei <bepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:42:07 by bepinhei          #+#    #+#             */
/*   Updated: 2025/10/25 20:42:07 by bepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

void	handle_w_equal_sign(char *env_var, char *equal_sign)
{
	int	j;

	j = 0;
	safe_putstr_fd("declare -x ", 1);
	while (env_var[j] != '=')
	{
		if (write(1, &env_var[j], 1) == -1)
			return ;
		j++;
	}
	safe_putstr_fd("=\"", 1);
	safe_putstr_fd(equal_sign + 1, 1);
	safe_putstr_fd("\"\n", 1);
}

void	print_env_var(char *env_var)
{
	char	*equal_sign;
	int		j;

	equal_sign = ft_strchr(env_var, '=');
	if (equal_sign)
		handle_w_equal_sign(env_var, equal_sign);
	else
	{
		j = 0;
		write(1, "declare -x ", 11);
		while (env_var[j])
		{
			if (write(1, &env_var[j], 1) == -1)
				return ;
			j++;
		}
		write(1, "\n", 1);
	}
}

int	sort_envp(char **envp)
{
	int		i;
	int		swap;
	char	*temp;

	i = 0;
	swap = 1;
	if (!envp)
		return (1);
	while (swap)
	{
		swap = 0;
		i = 0;
		while (envp[i] && envp[i + 1])
		{
			if (ft_strcmp(envp[i], envp[i + 1]) > 0)
			{
				temp = envp[i];
				envp[i] = envp[i + 1];
				envp[i + 1] = temp;
				swap = 1;
			}
			i++;
		}
	}
	return (0);
}

int	sanity_check_export(const char *var)
{
	int		i;
	int		var_len;

	if (!var || !var[0])
		return (FAILURE);
	var_len = 0;
	while (var[var_len] && var[var_len] != '='
		&& !(var[var_len] == '+' && var[var_len + 1] == '='))
		var_len++;
	if (var_len == 0)
		return (FAILURE);
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (FAILURE);
	i = 1;
	while (i < var_len)
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	builtin_export_no_var(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (1);
	if (sort_envp(envp))
		return (1);
	while (envp[i])
	{
		print_env_var(envp[i]);
		i++;
	}
	return (0);
}
