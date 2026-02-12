/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepinhei <bepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:43:08 by bepinhei          #+#    #+#             */
/*   Updated: 2025/10/25 21:45:29 by bepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

int	builtin_exit(char **argv, t_shell *shell, t_tkn *tokens)
{
	(void)tokens;
	if (argv && argv[1] && !is_valid_number(argv[1]) && !is_sign(argv[1]))
	{
		safe_putstr_fd("minishell: exit: ", 2);
		safe_putstr_fd(argv[1], 2);
		safe_putstr_fd(": numeric argument required\n", 2);
		shell->exit_status = 2;
		shell->flag_exit = true;
		return (shell->exit_status);
	}
	if (argv && argv[1] && argv[2])
	{
		safe_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->exit_status = 1;
		return (shell->exit_status);
	}
	if (argv && argv[1])
		shell->exit_status = parse_exit_number(argv[1]);
	write(1, "exit\n", 5);
	shell->flag_exit = true;
	return (shell->exit_status);
}
