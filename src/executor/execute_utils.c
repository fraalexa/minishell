/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 00:00:00 by berna             #+#    #+#             */
/*   Updated: 2026/03/06 13:45:39 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

void	child_exit(t_shell *shell, int status)
{
	fflush(NULL);
	if (shell && shell->ast_root)
		ast_free(shell->ast_root);
	if (shell)
		free_shell(shell);
	rl_clear_history();
	_exit(status);
}

char	*expand_variable_command(char *cmd_name, char **envp)
{
	(void)envp;
	if (!cmd_name)
		return (NULL);
	return (ft_strdup(cmd_name));
}

void	handle_path_not_found(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		safe_putstr_fd(cmd, 2);
		safe_putstr_fd(": No such file or directory\n", 2);
	}
	else
	{
		safe_putstr_fd(cmd, 2);
		safe_putstr_fd(": command not found\n", 2);
	}
}
