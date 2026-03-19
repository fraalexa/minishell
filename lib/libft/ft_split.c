/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:37:49 by fraalexa          #+#    #+#             */
/*   Updated: 2025/04/17 23:41:15 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			len++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (len);
}

static void	freeall(char **s1)
{
	int	i;

	i = 0;
	while (s1[i])
		free(s1[i++]);
	free(s1);
}

static int	strcpy1(char **ret, char *s, int posi, int posf)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = posf - posi;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
	{
		return (0);
	}
	while (posi < posf)
	{
		res[i++] = s[posi++];
	}
	res[i] = '\0';
	*ret = res;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		k;
	char	**res;
	int		posi;

	res = (char **)ft_calloc((count_words(s, c) + 1), sizeof(char *));
	i = 0;
	k = 0;
	posi = 0;
	if (!res || !s)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		posi = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > posi)
			if (!strcpy1(&res[k++], (char *)s, posi, i))
				return (freeall(res), NULL);
	}
	return (res);
}

/*
#include <stdio.h>
int main()
{
    int i;

	i = 0;
	char **test;
    //test = ft_split(" Tripouille ", ' ');

	test = ft_split("\11\11\11\11hello!\11\11\11\11", '\0');
	while (test[i])
    printf("%s\n" , test[i++]);
	i = 0;


}
*/
