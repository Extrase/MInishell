/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:56:35 by thenry            #+#    #+#             */
/*   Updated: 2022/11/15 21:13:47 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *)s;
	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return (str + i);
		i--;
	}
	return (NULL);
}

/*
#include <string.h>
#include <stdio.h>
int main()
{
	char str2[] = "bonjour";
	printf("%s, %p\n", ft_strrchr(str2, '\0'), ft_strrchr(str2, '\0'));
	printf("%s, %p\n", strrchr(str2, '\0'), strrchr(str2, '\0'));
	return 0;
}
*/
