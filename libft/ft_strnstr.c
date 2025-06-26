/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:03:54 by thenry            #+#    #+#             */
/*   Updated: 2022/11/21 11:51:24 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] && i + j < len)
	{
		if (big[i + j] == little[j])
		{
			if (little[++j] == '\0')
				return ((char *)big + i);
		}
		else
		{	
			j = 0;
			i++;
		}
	}
	return (NULL);
}

/*
#include <bsd/string.h>
#include <stdio.h>
int	main()
{
	char *big = "lorem ipsum dolor sit amet";
	char *little = "dolor";
	char *big2 = "lorem ipsum dolor sit amet";
	char *little2 = "dolor";
	printf("%s %p\n", ft_strnstr(big, little, 15), ft_strnstr(big, little, 15));
	printf("%s %p\n", strnstr(big2, little2, 15), strnstr(big2, little2, 15));
	return (0);
}
*/
