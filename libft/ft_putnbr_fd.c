/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:09:40 by thenry            #+#    #+#             */
/*   Updated: 2022/11/15 14:41:52 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	i;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	i = n;
	if (i > 9)
	{
		ft_putnbr_fd(i / 10, fd);
		i = i % 10;
	}
	ft_putchar_fd(i + '0', fd);
}

/*
#include <limits.h>
int	main()
{
	ft_putnbr_fd(INT_MIN, 1);
}
*/
