/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:23:38 by thenry            #+#    #+#             */
/*   Updated: 2022/11/15 14:38:34 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*tmp;

	tmp = s;
	while (n)
	{
		*tmp = (char)c;
		tmp++;
		n--;
	}
	return (s);
}

/*
#include <stdio.h>
#include <string.h>
int main()
{
	int i = 0;
        char str[] = "hello world";
	int tab[3] = {1, 2, 3};

	//test str
        printf("%s\n", str);
        ft_memset(str, 'f', sizeof(str));
        printf("%s\n", str);

	//test tab
	while (i < 3)
	{
		printf("%d\n", tab[i]);
		i++;
	}
	i = 0;
	ft_memset(tab, 0, sizeof(tab));
	while (i < 3)
	{
		printf("%d\n", tab[i]);
		i++;
	}
        return 0;
}
*/
