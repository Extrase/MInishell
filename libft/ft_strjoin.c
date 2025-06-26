/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:58:42 by thenry            #+#    #+#             */
/*   Updated: 2022/11/15 18:51:11 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		len1;
	size_t		len2;
	size_t		i;
	char		*str;

	if (s1 && s2)
	{
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		str = (char *)malloc((len1 + len2 + 1) * sizeof(char));
		if (!str)
			return (NULL);
		i = -1;
		while (s1[++i])
			str[i] = s1[i];
		i = -1;
		while (s2[++i])
			str[len1 + i] = s2[i];
		str[len1 + i] = '\0';
		return (str);
	}
	return (NULL);
}

/*
#include <stdio.h>
int	main()
{
	char	*s1 = "";
	char	*s2 = "dolor sit amet";

	printf("%s\n", ft_strjoin(s1, s2));
	return (0);
}
*/
