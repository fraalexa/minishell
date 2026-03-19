/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections_heredoc_utils.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 00:00:00 by fraalexa          #+#    #+#             */
/*   Updated: 2026/02/25 03:29:33 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

char	*read_heredoc_line(void)
{
	char		*line;
	char		c;
	ssize_t		bytes;

	if (isatty(STDIN_FILENO))
		return (readline("> "));
	line = ft_strdup("");
	if (!line)
		return (NULL);
	while (1)
	{
		bytes = read(STDIN_FILENO, &c, 1);
		if (bytes <= 0 || c == '\n')
			break ;
		line = ft_charjoin(line, c);
		if (!line)
			return (NULL);
	}
	if (bytes <= 0 && line[0] == '\0')
		return (free(line), NULL);
	return (line);
}

int	heredoc_warn_eof(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document delimited by eof", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putendl_fd("')", 2);
	return (SUCCESS);
}

int	is_heredoc_end(char *line, char *file)
{
	char	*delimiter;
	int		len;
	char	quote;
	int		match;

	if (!file)
		return (0);
	len = ft_strlen(file);
	quote = file[0];
	if (len >= 2 && (quote == '\'' || quote == '"') && file[len - 1] == quote)
		delimiter = ft_substr(file, 1, len - 2);
	else
		delimiter = ft_strdup(file);
	if (!delimiter)
		return (0);
	match = (ft_strcmp(line, delimiter) == 0);
	free(delimiter);
	return (match);
}

static char	*expand_heredoc_payload(t_shell *shell, char *line)
{
	char	*payload;
	int		i;

	payload = ft_strdup("");
	if (!payload)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1])
			payload = append_expansion(payload, line, shell, &i);
		else
		{
			payload = append_char_to_result(payload, line[i]);
			i++;
		}
		if (!payload)
			return (NULL);
	}
	return (payload);
}

int	write_heredoc_payload(t_shell *shell, int fd, char *line, int expand_vars)
{
	char	*payload;

	if (!expand_vars)
		payload = line;
	else
	{
		payload = expand_heredoc_payload(shell, line);
		if (!payload)
			return (free(line), FAILURE);
	}
	if (write(fd, payload, ft_strlen(payload)) == -1
		|| write(fd, "\n", 1) == -1)
		return (free(payload), free(line), FAILURE);
	if (expand_vars)
		free(payload);
	free(line);
	return (SUCCESS);
}
