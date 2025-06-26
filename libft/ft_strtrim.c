/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:29:32 by thenry            #+#    #+#             */
/*   Updated: 2022/11/16 17:41:42 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_start(const char *s1, const char *set)
{
	size_t	start;
	size_t	len;

	len = ft_strlen(s1);
	start = 0;
	while (start < len)
	{
		if (ft_strchr(set, s1[start]) == 0)
			break ;
		start++;
	}
	return (start);
}

static int	ft_end(const char *s1, const char *set)
{
	size_t		end;

	end = ft_strlen(s1);
	while (end > 0)
	{
		if (ft_strrchr(set, s1[end - 1]) == 0)
			break ;
		end--;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*tr;
	int		start;
	int		end;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = ft_start(s1, set);
	end = ft_end(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	tr = (char *)malloc((end - start) * sizeof(char) + 1);
	if (tr == NULL)
		return (NULL);
	ft_strlcpy(tr, s1 + start, end - start + 1);
	return (tr);
}

/*
#include <stdio.h>
int main()
{
	char	*str;
	char	*set;
	char	*trim;

	str = "lorem \n ipsum \t dolor \n sit \t amet";
	set = " ";
	trim = ft_strtrim(str, set);
	printf("%s\n", trim);
	return 0;
}
*/
