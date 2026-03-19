/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:38:52 by fraalexa          #+#    #+#             */
/*   Updated: 2025/04/15 20:39:10 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlen1(const char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

static int	check(char c, const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*res;
	int		i;
	int		k;

	len = ft_strlen1(s1);
	i = 0;
	k = len - 1;
	while (s1[i] && check(s1[i], set))
		i++;
	while (k > i && (check(s1[k], set)))
		k--;
	res = malloc(k - i + 2);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1 + i, k - i + 1);
	res[k - i + 1] = 0;
	return (res);
}
