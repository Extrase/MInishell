/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:27:14 by thenry            #+#    #+#             */
/*   Updated: 2022/11/15 14:48:35 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (dst == 0 || src == 0)
		return (0);
	if (size > 0)
	{
		--size;
		while (src[i] != '\0' && size != 0)
		{
			dst[i] = src[i];
			i++;
			size--;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

/*
#include <bsd/bsd.h>
#include <string.h>
#include <stdio.h>
int main()
{
	char *str = "hello tenny";
	char *str2 = "hello tenny";
	char cpy[20];
	char cpy2[20];
	printf("ma fonction = %ld\n", ft_strlcpy(cpy, str, 11));
	printf("str = %s\n", str);
	printf("cpy = %s\n", cpy);
	printf("vrai fonction = %ld\n", strlcpy(cpy2, str2, 11));
	printf("str2 = %s\n", str2);
	printf("cpy2 = %s\n", cpy2);
	return 0;
}
*/
