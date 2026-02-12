/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepinhei <bepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 18:33:02 by bepinhei          #+#    #+#             */
/*   Updated: 2025/10/25 18:33:02 by bepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

static int	echo_is_n_flag(char *arg)
{
	int	j;

	j = 1;
	if (!arg || arg[0] != '-')
		return (0);
	while (arg[j] == 'n')
		j++;
	return (arg[j] == '\0' && j > 1);
}

int	builtin_echo(char **argv, t_shell *shell, t_tkn *tokens)
{
	int	i;
	int	newline;

	(void)shell;
	(void)tokens;
	i = 1;
	newline = 1;
	while (argv[i] && echo_is_n_flag(argv[i]))
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	if (shell && shell->non_interactive)
		fflush(stdout);
	return (0);
}
