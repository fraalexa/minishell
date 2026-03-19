/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:05:28 by fraalexa          #+#    #+#             */
/*   Updated: 2025/04/15 19:07:58 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;

	if (size && nmemb > (SIZE_MAX / size))
		return (NULL);
	res = malloc(size * nmemb);
	if (res == NULL)
	{
		return (res);
	}
	ft_bzero(res, (nmemb * size));
	return (res);
}
