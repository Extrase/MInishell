/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:04:10 by thenry            #+#    #+#             */
/*   Updated: 2022/11/18 13:52:58 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != c && ft_isascii(c))
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return (str);
}

/*
#include <string.h>
#include <stdio.h>
int main()
{
	char str[] = "hello 0 world";
	char a = 0;
	printf("%s, %p\n", ft_strchr(str, a), ft_strchr(str, a));
	printf("%s, %p\n", strchr(str, a), strchr(str, a));
	return 0;
}
*/
