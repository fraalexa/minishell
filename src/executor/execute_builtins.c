/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:44:11 by bepinhei          #+#    #+#             */
/*   Updated: 2026/02/27 18:48:45 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

static int	handle_exit_builtin(t_shell *shell, char **args)
{
	int	idx;

	if (isatty(STDIN_FILENO))
		safe_putstr_fd("exit\n", STDOUT_FILENO);
	idx = 1;
	if (args && args[1] && ft_strncmp(args[1], "--", 3) == 0)
		idx = 2;
	if (idx == 2 && (!args || !args[idx]))
		return (shell->flag_exit = true, shell->exit_status = 0, 0);
	if (args && args[idx] && !is_valid_number(args[idx]))
	{
		safe_putstr_fd("minishell: exit: ", 2);
		safe_putstr_fd(args[idx], 2);
		safe_putstr_fd(": numeric argument required\n", 2);
		shell->exit_status = 2;
		shell->flag_exit = true;
		return (2);
	}
	if (args && args[idx] && args[idx + 1])
		return (safe_putstr_fd("minishell: exit: too many arguments\n", 2),
			shell->exit_status = 1, 1);
	shell->flag_exit = true;
	if (args && args[idx])
		shell->exit_status = parse_exit_number(args[idx]);
	return (shell->exit_status);
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
		result = builtin_echo(args, shell);
	else if (cmd_type == CMD_CD)
		result = builtin_cd(args, shell->envp);
	else if (cmd_type == CMD_PWD)
		result = builtin_pwd(shell);
	else if (cmd_type == CMD_UNSET)
		result = builtin_unset(args, &shell->envp);
	else if (cmd_type == CMD_ENV)
		result = builtin_env(shell->envp, shell);
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
