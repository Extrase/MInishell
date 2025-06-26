/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:23:09 by thenry            #+#    #+#             */
/*   Updated: 2022/11/15 19:24:52 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	i = 0;
	d = dest;
	s = src;
	if (d > s)
	{
		while (i < n)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
	}
	else
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}

/*
#include <stdio.h>
#include <string.h>
int main()
{
	//test tab
	int tab[] = {3, 65, 78, 29, 50};
	int *cpy = NULL;
	size_t len = sizeof(int) * 5;
	int i = 0;

	cpy = (int *)malloc(len);
	if (cpy == NULL)
		return (0);
	ft_memmove(cpy, tab, len);
	while (i < 5)
	{
		printf("%d\n", cpy[i]);
		i++;
	}

	//test str
	char str[] = "hello world";
	char *cpystr = NULL;
	size_t strlen = sizeof(str);

	cpystr = (char *)malloc(strlen);
	if (cpystr == NULL)
		return (0);
	ft_memmove(cpystr, str, strlen);
	printf("%s\n", cpystr);
	return (0);
}
*/
