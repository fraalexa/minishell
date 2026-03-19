/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:38:21 by fraalexa          #+#    #+#             */
/*   Updated: 2025/04/15 20:17:32 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	lensrc;

	lensrc = ft_strlen(src);
	if (size > 0)
	{
		while (*src && (size - 1))
		{
			*dst = *src;
			dst++;
			src++;
			size--;
		}
		*dst = 0;
	}
	return (lensrc);
}
