/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:52:20 by thenry            #+#    #+#             */
/*   Updated: 2022/11/15 14:36:40 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((int)((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]));
		i++;
	}
	return (0);
}

/*
#include <stdio.h>
#include <string.h>
int main()
{
	//test tab	
	int tab[] = {2, 8, 7, 10};
	int tab2[] = {2, 8, 9, 10};
	
	printf("%d\n", memcmp(tab, tab2, sizeof(tab)));
	printf("%d\n", ft_memcmp(tab, tab2, sizeof(tab)));

	//test str
	char str[] = "hello world";
	char str2[] = "hello tenny";
	
	printf("%d\n", ft_memcmp(str, str2, sizeof(str)));
	printf("%d\n", memcmp(str, str2, sizeof(str)));
	return (0);
}
*/
