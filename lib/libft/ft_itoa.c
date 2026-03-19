/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:17:39 by fraalexa          #+#    #+#             */
/*   Updated: 2025/04/15 19:25:01 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lenght(int n)
{
	int	len;

	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int num)
{
	int		len;
	char	*res;
	long	n;

	n = num;
	len = lenght(num);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[len--] = '\0';
	if (n < 0)
	{
		res[0] = '-';
		n = -n;
	}
	if (n == 0)
		res[0] = '0';
	while (n > 0)
	{
		res[len--] = (n % 10) + '0';
		n /= 10;
	}
	return (res);
}
/*
#include <stdio.h>
int main()
{
	printf("%s", ft_itoa(0));
	printf("%s", ft_itoa(-2147483648));
	printf("%s", ft_itoa(-2000000000));
}
*/