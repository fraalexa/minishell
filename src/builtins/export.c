/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepinhei <bepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:43:38 by bepinhei          #+#    #+#             */
/*   Updated: 2025/10/25 21:45:29 by bepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

int	handle_variable_update(t_shell *shell, t_exp *exp, const char *new_var)
{
	int	update_var;
	int	update_var_ex;

	update_var_ex = update_existing_variable_env(&shell->ex_envp, exp);
	if (update_var_ex == 1)
		return (free(exp->var), 1);
	if (exp->equal_sign)
	{
		update_var = update_existing_variable(&shell->envp, exp);
		if (update_var == 1)
			return (free(exp->var), 1);
		if (update_var == 2)
			if (add_new_variable_env(&shell->envp, exp, new_var))
				return (free(exp->var), 1);
	}
	if (update_var_ex == 2)
		if (add_new_variable(&shell->ex_envp, exp, new_var))
			return (free(exp->var), 1);
	return (0);
}

int	builtin_export(t_shell *shell, char ***envp, const char *new_var)
{
	t_exp	exp;

	(void)envp;
	if (parse_variable(new_var, &exp))
	{
		safe_putstr_fd("minishell: export: `", 2);
		safe_putstr_fd(new_var, 2);
		safe_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	if (!exp.equal_sign && !exp.add_sign && !exp.remove_sign)
	{
		if (!variable_exists(&shell->ex_envp, exp.var))
			if (add_new_variable(&shell->ex_envp, &exp, new_var))
				return (free(exp.var), 1);
		return (free(exp.var), 0);
	}
	if (handle_variable_update(shell, &exp, new_var))
		return (1);
	free(exp.var);
	return (0);
}
