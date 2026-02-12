/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 04:40:24 by fraalexa          #+#    #+#             */
/*   Updated: 2026/02/12 04:40:24 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

char	*build_prompt(t_shell *shell)
{
	char	*line;

	line = readline("minishell$ ");
	if (g_signal == 130)
	{
		shell->exit_status = 130;
		g_signal = 0;
	}
	if (!line)
	{
		printf("exit\n");
		free_arg(shell->envp);
		free_arg(shell->ex_envp);
		if (shell->heredoc)
		{
			free_heredoc(shell->heredoc);
			shell->heredoc = NULL;
		}
		exit(shell->exit_status);
	}
	else if (line[0] == '\0')
		return (NULL);
	return (line);
}
