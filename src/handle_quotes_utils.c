/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:58:50 by thenry            #+#    #+#             */
/*   Updated: 2023/11/08 20:05:04 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	condition(char *token, int i)
{
	if (token[i] == '$' && token[i + 1] && token[i + 1] != ' '
		&& token[i + 1] != '$' && token[i + 1] != '\"')
		return (1);
	else
		return (0);
	return (0);
}

void	dollar_iteration(char *token, int *i)
{
	while (token[*i] == '$')
		(*i)++;
}
