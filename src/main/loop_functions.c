/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:47:12 by bepinhei          #+#    #+#             */
/*   Updated: 2026/02/12 04:44:31 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

int	shell_loop(t_shell *shell)
{
	int	res;

	while (1)
	{
		setup_signals();
		init_shell_struct(shell);
		shell->line = readline("minishell$ ");
		if (!shell->line)
		{
			printf("exit\n");
			break ;
		}
		res = handle_interactive_line(shell);
		if (shell->flag_exit)
			break ;
		if (res)
			continue ;
	}
	return (shell->exit_status);
}
