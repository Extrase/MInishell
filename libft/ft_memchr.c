/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:02:06 by thenry            #+#    #+#             */
/*   Updated: 2022/11/17 17:01:12 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char		*a;
	size_t					i;

	i = 0;
	a = (const unsigned char *)s;
	while (i < n)
	{
		if (a[i] == (unsigned char)c)
			return ((void *)&a[i]);
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>
int main()
{
	//test tab	
	int tab[] = {2, 8, 7, 10};
	int b = 3;
	
	printf("%p\n", memchr(tab, b, sizeof(tab)));
	printf("%p\n", ft_memchr(tab, b, sizeof(tab)));

	//test str
	char str[] = "hello world";
	char a = 'o';
	
	printf("%p\n", memchr(str, a, sizeof(str)));
	printf("%p\n", ft_memchr(str, a, sizeof(str)));
	return (0);
}
*/
