/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:52:03 by thenry            #+#    #+#             */
/*   Updated: 2022/11/15 16:38:19 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(long int nb)
{
	int	k;

	k = 0;
	if (nb == 0)
		return (k = 1);
	if (nb < 0)
	{
		nb = -nb;
		k++;
	}
	while (nb > 0)
	{
		nb /= 10;
		k++;
	}
	return (k);
}

char	*ft_itoa(int n)
{
	char		*s;
	long int	nb;
	int			k;

	nb = n;
	k = ft_count(nb);
	s = (char *)malloc(k * sizeof(char) + 1);
	if (s == NULL)
		return (NULL);
	s[k] = '\0';
	k--;
	if (nb == 0 || nb == -0)
		s[0] = '0';
	else if (nb < 0)
	{
		s[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		s[k] = nb % 10 + '0';
		nb = nb / 10;
		k--;
	}
	return (s);
}

/*
#include <limits.h>
#include <stdio.h>
int main()
{
	int nb = -0;
	printf("%s\n", ft_itoa(nb));
	return (0);
}
*/
