/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:44:11 by bepinhei          #+#    #+#             */
/*   Updated: 2026/02/12 04:17:48 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

static int	handle_exit_builtin(t_shell *shell, char **args)
{
	int	result;

	if (isatty(STDIN_FILENO))
		safe_putstr_fd("exit\n", STDOUT_FILENO);
	if (args && args[1] && !is_valid_number(args[1]) && !is_sign(args[1]))
	{
		safe_putstr_fd("minishell: exit: ", 2);
		safe_putstr_fd(args[1], 2);
		safe_putstr_fd(": numeric argument required\n", 2);
		shell->exit_status = 2;
		shell->flag_exit = true;
		result = 2;
		return (result);
	}
	else if (args && args[1] && args[2])
	{
		safe_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->exit_status = 1;
		result = 1;
		return (result);
	}
	shell->flag_exit = true;
	if (args && args[1])
		shell->exit_status = parse_exit_number(args[1]);
	return (result = shell->exit_status, result);
}

static int	handle_export_builtin(t_shell *shell, char **args)
{
	int	result;

	if (!args[1])
		result = builtin_export_no_var(shell->envp);
	else
		result = builtin_export(shell, &shell->envp, args[1]);
	return (result);
}

static int	handle_basic_builtins(char **args, t_shell *shell,
		t_cmd_group cmd_type)
{
	int	result;

	if (cmd_type == CMD_ECHO)
		result = builtin_echo(args, shell, NULL);
	else if (cmd_type == CMD_CD)
		result = builtin_cd(args, shell->envp);
	else if (cmd_type == CMD_PWD)
		result = builtin_pwd(shell, NULL);
	else if (cmd_type == CMD_UNSET)
		result = builtin_unset(args, &shell->envp);
	else if (cmd_type == CMD_ENV)
		result = builtin_env(shell->envp, shell, NULL);
	else
		result = SUCCESS;
	return (result);
}

static void	finalize_builtin_execution(t_shell *shell, int result)
{
	shell->exit_status = result;
	if (shell->non_interactive)
		fflush(stdout);
}

int	execute_builtin(t_shell *shell, char **args, t_cmd_group cmd_type)
{
	int	result;

	if (cmd_type == CMD_EXPORT)
		result = handle_export_builtin(shell, args);
	else if (cmd_type == CMD_EXIT)
		result = handle_exit_builtin(shell, args);
	else
		result = handle_basic_builtins(args, shell, cmd_type);
	finalize_builtin_execution(shell, result);
	return (result);
}
