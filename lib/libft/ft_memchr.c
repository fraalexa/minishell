/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:30:45 by fraalexa          #+#    #+#             */
/*   Updated: 2025/04/15 19:34:38 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*clns;
	unsigned char	c1;

	clns = (unsigned char *)s;
	c1 = (unsigned char)c;
	while (n--)
	{
		if (*clns == c1)
			return (clns);
		clns++;
	}
	return (0);
}
