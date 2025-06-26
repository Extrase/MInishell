/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:12:35 by thenry            #+#    #+#             */
/*   Updated: 2022/11/15 15:52:44 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*tmp;

	tmp = s;
	while (n)
	{
		*tmp = 0;
		tmp++;
		n--;
	}		
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
        ft_bzero(str, 5);
        printf("%s\n", str);

	//test tab
	while (i < 3)
	{
		printf("%d\n", tab[i]);
		i++;
	}
	i = 0;
	ft_bzero(tab, sizeof(tab));
	while (i < 3)
	{
		printf("%d\n", tab[i]);
		i++;
	}
        return 0;
}
*/
