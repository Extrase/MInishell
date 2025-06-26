/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:37:18 by thenry            #+#    #+#             */
/*   Updated: 2022/11/15 14:51:18 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(ft_strlen(s) * sizeof(char) + 1);
	if (str == NULL)
		return (NULL);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*
#include <stdio.h>
char	to_upper(unsigned int i, char c)
{
	if (c >= 97 && c <= 122)
		c = c - 32;
	return (c);
}

int	main()
{
	char *str = "hello world";
	printf("%s\n", ft_strmapi(str, to_upper));
	return (0);
}
*/
