/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 00:16:19 by thenry            #+#    #+#             */
/*   Updated: 2022/11/15 16:06:43 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	char	*src;
	int		len;
	int		i;

	i = 0;
	src = (char *)s;
	len = ft_strlen(src) + 1;
	dup = (char *)malloc(len * sizeof(char));
	if (dup == NULL)
		return (NULL);
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/*
#include <stdio.h>
int main()
{
	char *str = "hello la";
	printf("%s\n", ft_strdup(str));
	return 0;
}
*/
