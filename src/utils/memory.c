/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:27:27 by bepinhei          #+#    #+#             */
/*   Updated: 2026/02/12 02:29:36 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

void	free_heredoc(t_heredoc *heredoc)
{
	t_heredoc	*tmp;

	while (heredoc)
	{
		tmp = heredoc->next;
		if (heredoc->fd_heredoc_path)
		{
			free(heredoc->fd_heredoc_path);
			heredoc->fd_heredoc_path = NULL;
		}
		free(heredoc);
		heredoc = NULL;
		heredoc = tmp;
	}
}

int	free_array(char **str, int error)
{
	int	i;

	if (!str)
		return (error);
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
	return (error);
}

void	free_arg(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i])
	{
		free(argv[i]);
		argv[i] = NULL;
		i++;
	}
	free(argv);
	argv = NULL;
}
