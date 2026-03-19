/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:37:13 by fraalexa          #+#    #+#             */
/*   Updated: 2025/04/15 20:49:36 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*cpd;
	unsigned char	*cps;

	cpd = (unsigned char *) dest;
	cps = (unsigned char *) src;
	if (cpd < cps)
	{
		while (n--)
		{
			*cpd++ = *cps++;
		}
	}
	else if (cpd > cps)
	{
		cps += n;
		cpd += n;
		while (n)
		{
			*--cpd = *--cps;
			n--;
		}
	}
	return (dest);
}
