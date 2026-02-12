/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:25:06 by bepinhei          #+#    #+#             */
/*   Updated: 2026/02/12 02:29:36 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

void	ft_close(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	safe_putstr_fd(const char *s, int fd)
{
	ft_putstr_fd((char *)s, fd);
}
