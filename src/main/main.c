/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:47:25 by bepinhei          #+#    #+#             */
/*   Updated: 2026/02/12 04:11:56 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

volatile int	g_signal = 0;

void	free_shelo(t_shell *shell)
{
	if (shell->envp)
		free_arg(shell->envp);
	if (shell->ex_envp)
		free_arg(shell->ex_envp);
	if (shell->path)
		free_arg(shell->path);
	if (shell->arg)
		free_arg(shell->arg);
	if (shell->user)
		free(shell->user);
	if (shell->home)
		free(shell->home);
	if (shell->hostname)
		free(shell->hostname);
	if (shell->pwd)
		free(shell->pwd);
	if (shell->prompt)
		free(shell->prompt);
	if (shell->line)
		free(shell->line);
	if (shell->word)
		free(shell->word);
}

void	free_shell(t_shell *shell)
{
	free_shelo(shell);
	if (shell->cmds)
	{
		if (shell->cmds->av)
			free_arg(shell->cmds->av);
		if (shell->cmds->cmd)
			free(shell->cmds->cmd);
		free(shell->cmds);
	}
	if (shell->heredoc)
		free_heredoc(shell->heredoc);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	int		exit_status;

	(void)ac;
	(void)av;
	ft_memset(&shell, 0, sizeof(t_shell));
	init_shell(&shell, envp);
	exit_status = shell_loop(&shell);
	free_shell(&shell);
	return (exit_status);
}
