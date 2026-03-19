/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepinhei <bepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:42:57 by bepinhei          #+#    #+#             */
/*   Updated: 2025/10/25 20:42:57 by bepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

int	builtin_env(char **envp, t_shell *shell)
{
	int	i;
	int	j;

	(void)shell;
	i = 0;
	while (envp && envp[i])
	{
		j = 0;
		while (envp[i][j])
		{
			if (write(1, &envp[i][j], 1) == -1)
				return (1);
			j++;
		}
		if (write(1, "\n", 1) == -1)
			return (1);
		i++;
	}
	return (0);
}
