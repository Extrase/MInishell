/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:34:07 by thenry            #+#    #+#             */
/*   Updated: 2023/10/13 17:34:58 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bool_history(char *prompt)
{
	int	i;

	i = 0;
	if (prompt[0] == '\0')
		return (0);
	while (prompt[i])
	{
		if (!ft_space(prompt[i]))
			return (1);
		i++;
	}
	return (0);
}
