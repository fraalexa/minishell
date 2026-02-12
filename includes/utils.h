/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:50:43 by bepinhei          #+#    #+#             */
/*   Updated: 2026/02/12 02:29:36 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

/* Memory / parsing cleanup */
void	free_parse(t_shell *shell);

/* Array utilities */
void	free_heredoc(t_heredoc *heredoc);
int		free_array(char **str, int error);
void	free_arg(char **argv);

/* File descriptors */
void	safe_putstr_fd(const char *s, int fd);
void	ft_close(int *fd);

/* String utilities */
char	*ft_strncat(char *dest, const char *src, size_t n);

#endif
