/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:38:15 by fraalexa          #+#    #+#             */
/*   Updated: 2025/04/15 20:15:16 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int		len;
	int		i;
	size_t	dstlen;
	int		sum;

	dstlen = ft_strlen(dst);
	len = size - 1 - dstlen;
	i = dstlen;
	if (size > dstlen)
		sum = dstlen + ft_strlen(src);
	else
		return (ft_strlen(src) + size);
	while (len && *src)
	{
		dst[i++] = *src;
		src++;
		len--;
	}
	dst[i] = 0;
	return (sum);
}
