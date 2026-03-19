/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:38:39 by fraalexa          #+#    #+#             */
/*   Updated: 2025/04/15 20:32:02 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *needle, size_t len)
{
	size_t	i;
	size_t	k;

	if (!*needle)
		return ((char *)s);
	i = 0;
	while (s[i] && i < len)
	{
		k = 0;
		while (needle[k] && s[i + k] == needle[k] && (i + k) < len)
			k++;
		if (!needle[k])
			return ((char *)(s + i));
		i++;
	}
	return (0);
}
