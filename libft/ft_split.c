/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:42:50 by thenry            #+#    #+#             */
/*   Updated: 2022/11/15 14:44:08 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wc(char *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static int	wl(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char	*ft_word(char *str, char c)
{
	int		i;
	int		wlen;
	char	*word;

	i = 0;
	wlen = wl(str, c);
	word = (char *)malloc(sizeof(char) * (wlen + 1));
	if (word == NULL)
		return (NULL);
	while (i < wlen)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	*str;
	char	**strs;

	i = 0;
	str = (char *)s;
	strs = (char **)malloc(sizeof(char *) * (wc(str, c) + 1));
	if (strs == NULL)
		return (NULL);
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str != '\0')
		{
			strs[i] = ft_word(str, c);
			i++;
		}
		while (*str && *str != c)
			str++;
	}
	strs[i] = 0;
	return (strs);
}

/*
#include <stdio.h>
int	main(int ac, char **av)
{
	int	i;
	char	**test;
	char	sep;

	sep = '-';
	(void)ac;	
	i = 0;
	test = ft_split(av[1], sep);
	while (test[i])
	{
		printf("%s\n", test[i]);
		i++;
	}
	return (0);
}
*/
