/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:35:03 by fraalexa          #+#    #+#             */
/*   Updated: 2025/04/15 20:49:15 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*clns1;
	unsigned char	*clns2;

	clns1 = (unsigned char *)s1;
	clns2 = (unsigned char *)s2;
	if (!n)
		return (0);
	n--;
	while (n && *clns1 == *clns2)
	{
		clns1++;
		clns2++;
		n--;
	}
	return (*clns1 - *clns2);
}
