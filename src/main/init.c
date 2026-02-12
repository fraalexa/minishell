/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:47:08 by bepinhei          #+#    #+#             */
/*   Updated: 2026/02/12 02:29:36 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

static void	init_heredoc(t_heredoc *heredoc)
{
	heredoc->i = 0;
	heredoc->count_hd = 0;
	heredoc->fd_heredoc_path = NULL;
	heredoc->eof = NULL;
	heredoc->next = NULL;
}

void	init_shell(t_shell *shell, char **envp)
{
	if (!shell->envp)
	{
		shell->envp = init_env(envp);
		shell->ex_envp = init_env(envp);
	}
	shell->cmds = NULL;
	increment_shlvl(shell->envp);
}

void	init_shell_struct(t_shell *shell)
{
	shell->path = NULL;
	shell->cmd_count = 0;
	shell->flag_redir = false;
	shell->flag_exit = false;
	shell->arg = NULL;
	if (shell->heredoc)
		free_heredoc(shell->heredoc);
	shell->heredoc = ft_calloc(1, sizeof(t_heredoc));
	init_heredoc(shell->heredoc);
}

char	**init_env(char **envp)
{
	char	**env_copy;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env_copy = malloc(sizeof(char *) * (i + 1));
	if (!env_copy)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		env_copy[i] = ft_strdup(envp[i]);
		if (!env_copy)
			return (NULL);
	}
	env_copy[i] = NULL;
	return (env_copy);
}
