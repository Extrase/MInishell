/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:54:20 by thenry            #+#    #+#             */
/*   Updated: 2023/11/08 20:04:57 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unclosed_singleq(char *token)
{
	int		k;
	int		i;

	k = 0;
	i = 0;
	while (token[i])
	{
		if (token[i] == '\'')
			k++;
		i++;
	}
	if (k % 2 == 0 || k == 0)
		return (0);
	g_exit_status = 1;
	return (ft_error("minishell: error: unclosed single quotes\n"), 1);
}

int	ft_unclosed_doubleq(char *token)
{
	int		k;
	int		i;

	k = 0;
	i = 0;
	while (token[i])
	{
		if (token[i] == '\"')
			k++;
		i++;
	}
	if (k % 2 == 0 || k == 0)
		return (0);
	g_exit_status = 1;
	return (ft_error("minishell: error: unclosed double quotes\n"), 1);
}

int	count_char(char c, char *token)
{
	int	i;

	i = 0;
	while (*token)
	{
		if (*token == c)
			i++;
		token++;
	}
	return (i);
}
