/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepinhei <bepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 00:00:00 by berna             #+#    #+#             */
/*   Updated: 2025/10/25 21:45:29 by bepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

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
