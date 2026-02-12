/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepinhei <bepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:43:02 by bepinhei          #+#    #+#             */
/*   Updated: 2025/10/25 20:43:02 by bepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/merge.h"

static int	check_digits(const char *str, int start)
{
	int	i;
	int	has_digits;

	i = start;
	has_digits = 0;
	if (str[i] == '"')
		i++;
	while (str[i] && str[i] != '"')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		has_digits = 1;
		i++;
	}
	if (str[i] == '"')
		i++;
	return (str[i] == '\0' && has_digits);
}

int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	return (check_digits(str, i));
}

static int	parse_digits(const char *str, int start)
{
	int	i;
	int	value;
	int	d;

	i = start;
	value = 0;
	if (!str || start < 0 || !str[start] || !isdigit((unsigned char)str[start]))
	{
		errno = EINVAL;
		perror("non numerical value");
		return (0);
	}
	while (str[i] && isdigit((unsigned char)str[i]))
	{
		d = str[i] - '0';
		if (value > (INT_MAX - d) / 10)
		{
			errno = ERANGE;
			perror("non numerical value");
			return (0);
		}
		value = value * 10 + d;
		i++;
	}
	return (value);
}

int	parse_exit_number(const char *str)
{
	int	sign;
	int	i;

	sign = 1;
	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	return (sign * parse_digits(str, i));
}

int	is_sign(char *argv)
{
	if (!argv || ft_strlen(argv) != 1)
		return (0);
	return ((ft_strncmp(argv, "+", 1) == 0) || (ft_strncmp(argv, "-", 1) == 0));
}
