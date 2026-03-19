/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:37:03 by fraalexa          #+#    #+#             */
/*   Updated: 2025/04/15 19:40:39 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void	*original_dest;

	original_dest = dest;
	if (!dest && !src)
		return (NULL);
	while (n)
	{
		*(unsigned char *)dest = *(unsigned char *)src;
		src = (unsigned char *)src + 1;
		dest = (unsigned char *)dest + 1;
		n--;
	}
	return (original_dest);
}
