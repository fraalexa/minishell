/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:43:02 by bepinhei          #+#    #+#             */
/*   Updated: 2026/02/27 18:48:45 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

static int	is_overflow(unsigned long long value, int digit, int negative)
{
	unsigned long long	limit;

	if (negative)
		limit = (unsigned long long)LLONG_MAX + 1ULL;
	else
		limit = (unsigned long long)LLONG_MAX;
	if (value > (limit - (unsigned long long)digit) / 10ULL)
		return (1);
	return (0);
}

static int	validate_digits_and_range(const char *str, int i, int negative)
{
	unsigned long long	value;
	int					digit;
	int					has_digits;

	value = 0;
	has_digits = 0;
	while (str[i] && ft_isdigit((unsigned char)str[i]))
	{
		digit = str[i] - '0';
		if (is_overflow(value, digit, negative))
			return (0);
		value = value * 10ULL + (unsigned long long)digit;
		has_digits = 1;
		i++;
	}
	if (!has_digits || str[i] != '\0')
		return (0);
	return (1);
}

int	is_valid_number(const char *str)
{
	int	i;
	int	negative;

	i = 0;
	negative = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative = 1;
		i++;
	}
	return (validate_digits_and_range(str, i, negative));
}

int	parse_exit_number(const char *str)
{
	int	sign;
	int	i;
	int	mod;

	sign = 1;
	i = 0;
	mod = 0;
	if (!str)
		return (0);
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && ft_isdigit((unsigned char)str[i]))
	{
		mod = (mod * 10 + (str[i] - '0')) % 256;
		i++;
	}
	if (sign == -1 && mod != 0)
		return (256 - mod);
	return (mod);
}

int	is_sign(char *argv)
{
	if (!argv || ft_strlen(argv) != 1)
		return (0);
	return ((ft_strncmp(argv, "+", 1) == 0) || (ft_strncmp(argv, "-", 1) == 0));
}
