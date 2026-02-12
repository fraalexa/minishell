/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepinhei <bepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:43:17 by bepinhei          #+#    #+#             */
/*   Updated: 2025/10/25 20:43:17 by bepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

int	find_existing_variable(char ***envp, t_exp **exp)
{
	int		i;
	size_t	var_len;
	char	*equal_pos;

	i = 0;
	var_len = ft_strlen((*exp)->var);
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], (*exp)->var, var_len) == 0
			&& ((*envp)[i][var_len] == '\0' || (*envp)[i][var_len] == '='))
		{
			equal_pos = ft_strchr((*envp)[i], '=');
			if (equal_pos)
				(*exp)->existing_value = equal_pos + 1;
			else
				(*exp)->existing_value = NULL;
			return (i);
		}
		i++;
	}
	return (-1);
}

int	update_existing_variable_env(char ***envp, t_exp *exp)
{
	int	i;

	exp->flag = 0;
	i = find_existing_variable(envp, &exp);
	if (i == -1)
		return (2);
	if (exp->add_sign)
	{
		if (handle_addition(exp))
			return (free(exp->var), 1);
	}
	else if (exp->remove_sign)
	{
		if (handle_removal(exp))
			return (free(exp->var), 1);
	}
	else
	{
		exp->updated_value = ft_strdup(exp->equal_sign + 1);
		if (!exp->updated_value)
			return (free(exp->var), 1);
	}
	if (update_variable_entry(envp, &exp, i))
		return (1);
	return (0);
}

int	parse_variable(const char *new_var, t_exp *exp)
{
	if (sanity_check_export(new_var) == FAILURE)
		return (1);
	exp->flag = 0;
	exp->len = ft_strlen(new_var);
	exp->equal_sign = ft_strnstr(new_var, "=", exp->len);
	exp->add_sign = ft_strnstr(new_var, "+=", exp->len);
	exp->remove_sign = ft_strnstr(new_var, "-=", exp->len);
	if (exp->add_sign)
		exp->var = ft_substr(new_var, 0, exp->add_sign - new_var);
	else if (exp->remove_sign)
		exp->var = ft_substr(new_var, 0, exp->remove_sign - new_var);
	else if (exp->equal_sign)
		exp->var = ft_substr(new_var, 0, exp->equal_sign - new_var);
	else
		exp->var = ft_strdup(new_var);
	return (exp->var == NULL);
}

int	variable_exists(char ***envp, const char *var)
{
	int		i;
	size_t	var_len;

	i = 0;
	var_len = ft_strlen(var);
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], var, var_len) == 0 &&
			((*envp)[i][var_len] == '\0' || (*envp)[i][var_len] == '='))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	add_new_variable_env(char ***envp, t_exp *exp, const char *new_var)
{
	int	i;

	i = 0;
	while ((*envp)[i])
		i++;
	exp->new_envp = malloc(sizeof(char *) * (i + 2));
	if (!exp->new_envp)
		return (free(exp->var), 1);
	i = 0;
	while ((*envp)[i])
	{
		exp->new_envp[i] = (*envp)[i];
		i++;
	}
	exp->new_entry = ft_strdup(new_var);
	if (!exp->new_entry)
		return (free(exp->new_envp), free(exp->var), 1);
	exp->new_envp[i] = exp->new_entry;
	exp->new_envp[i + 1] = NULL;
	free(*envp);
	*envp = exp->new_envp;
	return (0);
}
