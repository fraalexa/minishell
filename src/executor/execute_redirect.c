/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:44:23 by bepinhei          #+#    #+#             */
/*   Updated: 2026/03/18 17:44:22 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

void	restore_redirections(int *original_fds)
{
	if (original_fds[0] != -1)
	{
		dup2(original_fds[0], STDIN_FILENO);
		close(original_fds[0]);
	}
	if (original_fds[1] != -1)
	{
		dup2(original_fds[1], STDOUT_FILENO);
		close(original_fds[1]);
	}
}

t_cmd_group	get_cmd_type(char *cmd)
{
	if (!cmd)
		return (CMD_EXEC);
	if (ft_strcmp(cmd, "echo") == 0)
		return (CMD_ECHO);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (CMD_CD);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (CMD_PWD);
	else if (ft_strcmp(cmd, "export") == 0)
		return (CMD_EXPORT);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (CMD_UNSET);
	else if (ft_strcmp(cmd, "env") == 0)
		return (CMD_ENV);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (CMD_EXIT);
	return (CMD_EXEC);
}

static void	handle_external_child(t_shell *shell, char *path,
	char **args, char **envp)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		safe_putstr_fd(args[0], 2);
		safe_putstr_fd(": Is a directory\n", 2);
		free(path);
		child_exit(shell, 126);
	}
	execve(path, args, envp);
	if (errno == ENOEXEC)
	{
		free(path);
		child_exit(shell, 0);
	}
	safe_putstr_fd(args[0], 2);
	safe_putstr_fd(": ", 2);
	ft_putendl_fd((char *)strerror(errno), 2);
	free(path);
	if (errno == ENOENT)
		child_exit(shell, 127);
	else
		child_exit(shell, 126);
}

static int	handle_external_parent(char *path, pid_t pid)
{
	int	status;

	free(path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (SUCCESS);
}

int	execute_external(t_shell *shell, char **args)
{
	char	*path;
	pid_t	pid;

	if (!args || !args[0])
		return (SUCCESS);
	if (args[0][0] == '\0')
		return (handle_path_not_found(args[0]), 127);
	if (ft_strchr(args[0], '/'))
		path = ft_strdup(args[0]);
	else
		path = find_path(args[0], shell->envp);
	if (!path)
		return (handle_path_not_found(args[0]), 127);
	pid = fork();
	if (pid == -1)
		return (free(path), FAILURE);
	if (pid == 0)
	{
		restore_child_signals();
		handle_external_child(shell, path, args, shell->envp);
	}
	return (handle_external_parent(path, pid));
}
