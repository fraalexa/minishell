/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepinhei <bepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:43:43 by bepinhei          #+#    #+#             */
/*   Updated: 2025/10/25 20:43:43 by bepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

int	builtin_pwd(t_shell *shell)
{
	char	buf[PATH_MAX];

	(void)shell;
	if (getcwd(buf, sizeof(buf)))
		printf("%s\n", buf);
	else
		perror("pwd");
	fflush(stdout);
	return (0);
}
