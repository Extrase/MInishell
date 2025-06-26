/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:09:27 by thenry            #+#    #+#             */
/*   Updated: 2022/11/16 20:11:54 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*mem;

	if (size && nmemb * size / size != nmemb)
		return (NULL);
	mem = malloc(nmemb * size);
	if (mem == NULL)
		return (NULL);
	else
		ft_bzero(mem, nmemb * size);
	return (mem);
}

/*
#include <stdio.h>
int	main()
{
	int 	i = 0;
	int	a = 3;
	char	*pstr;
	int	*ptab;

	//test str
	pstr = (char *)ft_calloc(a, sizeof(char));
	while (i < a)
	{
		printf("%d, %p\n", pstr[i], &pstr[i]);
		i++;
	}
	free(pstr);

	//test tab
	i = 0;
	ptab = (int *)ft_calloc(a, sizeof(int));
	while (i < a)
	{
		printf("%d, %p\n", ptab[i], &ptab[i]);
		i++;
	}
	free(ptab);

	return 0;
}
*/
