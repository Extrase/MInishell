/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:38:12 by thenry            #+#    #+#             */
/*   Updated: 2022/11/18 19:33:25 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	i = 0;
	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (!size || size <= dlen)
		return (slen + size);
	while (src[i] && dlen + i < size - 1)
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (dlen + slen);
}

/*
#include <stdio.h>
#include <bsd/string.h>
int main()
{	
	//if size < destlen -> return srclen + size
	//else return destlen + srclen
	char dst[20] = "hello";
	char src[20] = "world";
	printf("strcat = %ld\n", ft_strlcat(dst, src, 10));
	return(0);
}
*/
