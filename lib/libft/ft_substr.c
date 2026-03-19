/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:38:57 by fraalexa          #+#    #+#             */
/*   Updated: 2025/04/17 23:49:19 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*res;
	unsigned int		posf;
	int					i;

	if (start >= ft_strlen(s))
	{
		res = ft_strdup("");
		return (res);
	}
	posf = start + len;
	if (start + len > ft_strlen(s))
		posf = ft_strlen(s);
	res = malloc(((posf - start) + 1));
	if (!res || s == 0)
		return (0);
	i = 0;
	while (start < posf)
	{
		res[i++] = s[start++];
	}
	res[i] = 0;
	return (res);
}
